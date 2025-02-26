/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:39:36 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/26 13:02:25 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*expand_heredoc(t_shell *shell, char *line)
{
	char	*result;

	if (!line)
		return (NULL);
	result = expand_string(shell, line);
	if (!result)
		return (NULL);
	return (result);
}

void	process_heredoc(t_shell *shell)
{
	char	*file_name;
	char	*idx_tmp;
	int		loop_status;

	while (shell->cmd->i_hd < shell->cmd->hd_count)
	{
		idx_tmp = ft_itoa(shell->cmd->i_hd);
		file_name = ft_strjoin2(".heredoc_", idx_tmp);
		free(idx_tmp);
		shell->exec->infile = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (shell->exec->infile < 0)
			err_message(shell, file_name, NULL, NULL);
		if (shell->cmd->last_file)
			free(shell->cmd->last_file);
		shell->cmd->last_file = ft_strdup(file_name);
		loop_status = loop_heredoc(shell);
		if (loop_status == 2)
		{
			unlink(shell->cmd->last_file);
			free(file_name);
			free(shell->cmd->last_file);
			close(shell->exec->infile);
			if (shell->exec->cmd_count == true)
			{
				perror("HERE");
				ft_exit(shell, shell->argv);
			}
			return ;
		}
		unlink(file_name);
		free(file_name);
		shell->cmd->i_hd++;
		close(shell->exec->infile);
	}
	redir_heredoc(shell, shell->cmd->last_file);
}

int	loop_heredoc(t_shell *shell)
{
	char	*line;
	char	*tmp;
	int		status;

	while (1)
	{
		line = readline("> ");
		status = interrupt_heredoc(shell, line);
		if (status >= 1)
			break ;
		if (!shell->cmd->is_quote)
		{
			tmp = expand_heredoc(shell, line);
			line = tmp;
		}
		ft_putendl_fd(line, shell->exec->infile);
		if (shell->cmd->is_quote)
			free(line);
	}
	free(line);
	return (status);
}

void	redir_heredoc(t_shell *shell, char *file)
{
	if (shell->exec->cmd_count)
	{
		fprintf(stderr, "i_hd = %d\n", shell->cmd->i_hd);
		fprintf(stderr, "hd_count = %d\n", shell->cmd->hd_count);
		if (shell->cmd->i_hd == shell->cmd->hd_count - 1)
		{
			if (shell->cmd->hd_count)
				shell->exec->infile = open(shell->cmd->last_file, 00, 0664);
			if (shell->exec->infile < 0)
				err_message(shell, shell->cmd->last_file, NULL, NULL);
			if (shell->exec->infile)
				err_message(shell, shell->cmd->last_file, NULL, NULL);
			if (dup2(shell->exec->infile, STDIN_FILENO) < 0)
				err_message(shell, shell->cmd->last_file, NULL, NULL);
		}
		close(shell->exec->infile);
		unlink(file);
		free(shell->cmd->last_file);
	}
	else
	{
		unlink(file);
		free(shell->cmd->last_file);
	}
	rl_clear_history();
}

int	interrupt_heredoc(t_shell *shell, char *line)
{
	if (g_signal)
	{
		shell->last_status = 128 + g_signal;
		g_signal = 0;
		return (2);
	}
	if (!line)
	{
		ft_putstr_fd("warning: here-document delimited by end-of-file '", 2);
		ft_putstr_fd(shell->cmd->limiter[shell->cmd->i_hd], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	if (ft_strcmp(line, shell->cmd->limiter[shell->cmd->i_hd]) == 0)
		return (1);
	return (0);
}
