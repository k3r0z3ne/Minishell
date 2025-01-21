#include "../../includes/exec.h"

// Update redirection type checks using enums from lexer.h
int redirection_check(t_shell *shell, t_exec *exec, t_redir *redirs)
{
    if (!redirs) 
		return 0;
    while (redirs)
	{
        if (redirs->type == REDIRIN)
            exec->infile = open(redirs->file, O_RDONLY);
        else if (redirs->type == REDIROUT)
            exec->outfile = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
        else if (redirs->type == APPEND)
            exec->outfile = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
        else if (redirs->type == HEREDOC)
            handle_here_doc(shell);
        if (exec->infile < 0 || exec->outfile < 0) 
			return -1;
        redirs = redirs->next;
    }
    return 0;
}
int redirect_setup(t_exec *exec, t_redir *redir)
{
    if (!redir)
        return (0);  // No redirections to handle
    // Apply any file redirections (these override pipe redirections)
    while (redir)
	{
        if (redir->type == REDIRIN)
		{
            int fd = open(redir->file, O_RDONLY);
            if (fd < 0)
                return (-1);
            if (dup2(fd, STDIN_FILENO) < 0)
			{
                close(fd);
                return (-1);
            }
            close(fd);
        }
        else if (redir->type == REDIROUT)
		{
            int fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                return (-1);
            if (dup2(fd, STDOUT_FILENO) < 0) {
                close(fd);
                return (-1);
            }
            close(fd);
        }
        else if (redir->type == APPEND)
		{
            int fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
                return (-1);
            if (dup2(fd, STDOUT_FILENO) < 0) {
                close(fd);
                return (-1);
            }
            close(fd);
        }
        else if (redir->type == HEREDOC)
		{
            // Assuming heredoc fd is already set up in exec->infile
            if (exec->infile != -1) {
                if (dup2(exec->infile, STDIN_FILENO) < 0)
                    return (-1);
                close(exec->infile);
            }
        }
        redir = redir->next;
    }
    return (0);
}

int	several_cmds(t_shell *shell)
{
    int prev_pipe[2] = {-1, -1};
    int curr_pipe[2];
    int i = 0;

    shell->exec->pids = tracked_malloc(shell, sizeof(pid_t) * shell->exec->cmd_count);
    while (shell->cmd && i < shell->exec->cmd_count)
	{
        if (i < shell->exec->cmd_count - 1)
		{
            if (pipe(curr_pipe) < 0) // Create pipe for all but the last command
                return (-1);
        }
        shell->exec->pids[i] = fork();
        if (shell->exec->pids[i] == 0) // Child process
		{
            // Setup input from previous pipe if it exists
            if (prev_pipe[0] != -1) 
			{
                dup2(prev_pipe[0], STDIN_FILENO);
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }
            if (i < shell->exec->cmd_count - 1) // Setup output to current pipe if not last command
			{
                close(curr_pipe[0]);
                dup2(curr_pipe[1], STDOUT_FILENO);
                close(curr_pipe[1]);
            }
            // Handle redirections
            if (redirect_setup(shell->exec, shell->cmd->redirs) < 0)
                exit(EXIT_FAILURE);
            exec_cmd(shell);
            exit(EXIT_FAILURE);
        }
        if (prev_pipe[0] != -1) // Parent process
		{
            close(prev_pipe[0]);
            close(prev_pipe[1]);
        }
        if (i < shell->exec->cmd_count - 1)
		{
            prev_pipe[0] = curr_pipe[0];
            prev_pipe[1] = curr_pipe[1];
        }
        shell->cmd = shell->cmd->next;
        i++;
    }
    for (i = 0; i < shell->exec->cmd_count; i++) // Wait for all child processes
        waitpid(shell->exec->pids[i], NULL, 0);
    return (0);
}

int wait_process(t_shell *shell, int n)
{
    int status;
    int exit_status = 0;
    pid_t wpid;

    for (int i = 0; i < n; i++)
	{
        wpid = waitpid(shell->exec->pids[i], &status, 0);
        if (wpid > 0)
		{
            if (WIFEXITED(status))
                exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                exit_status = 128 + WTERMSIG(status);
        }
    }
    return (exit_status);
}

int several_cmds(t_shell *shell)
{
    int pipe_fd[2];
    int old_pipe = -1;
    int i = 0;

    shell->exec->pids = tracked_malloc(shell, sizeof(pid_t) * shell->exec->cmd_count);
    while (shell->cmd && i < shell->exec->cmd_count)
	{
        if (i < shell->exec->cmd_count - 1)
		{
            if (pipe(pipe_fd) < 0)
                return (-1);
        }
        shell->exec->pids[i] = fork();
        if (shell->exec->pids[i] == 0)
		{
            if (old_pipe != -1) // Set up input from previous pipe
			{
                dup2(old_pipe, STDIN_FILENO);
                close(old_pipe);
            }
            
            if (i < shell->exec->cmd_count - 1) // Set up output to current pipe
			{
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            if (redirect_setup(shell->exec, shell->cmd->redirs) < 0)
                exit(EXIT_FAILURE);
            exec_cmd(shell);
            exit(EXIT_FAILURE);
        }
        if (old_pipe != -1) // Parent process
            close(old_pipe);
        if (i < shell->exec->cmd_count - 1)
		{
            close(pipe_fd[1]);
            old_pipe = pipe_fd[0];
        }
        shell->cmd = shell->cmd->next;
        i++;
    }
    for (i = 0; i < shell->exec->cmd_count; i++) // Wait for all child processes
        waitpid(shell->exec->pids[i], NULL, 0);    
    return (0);
}
