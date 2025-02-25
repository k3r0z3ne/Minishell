/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:39:36 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/25 14:35:38 by xenon            ###   ########.fr       */
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
 
	idx_tmp = ft_itoa(shell->cmd->i_hd);
	file_name = ft_strjoin2(".heredoc_", idx_tmp);
	free(idx_tmp);
	shell->exec->infile = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (shell->exec->infile < 0)
		err_exit(shell, "error opening file");
	if (shell->cmd->last_file)
		free(shell->cmd->last_file);
	shell->cmd->last_file = file_name;
	while (shell->cmd->i_hd < shell->cmd->hd_count)
	{
		loop_status = loop_heredoc(shell);
		shell->cmd->i_hd++;
	}
	close(shell->exec->infile);
	if (loop_status == 2)
	{
		unlink(file_name);
		return ;
	}
	redir_heredoc(shell, file_name);
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
	if (shell->cmd->i_hd == shell->cmd->hd_count)
	{
		if (shell->exec->cmd_count)
		{
			if (shell->cmd->hd_count)
				shell->exec->infile = open(shell->cmd->last_file, 00, 0664);
			if (shell->exec->infile < 0)
				err_exit(shell, "error opening file");
			if (dup2(shell->exec->infile, STDIN_FILENO) < 0)
				err_exit(shell, "dup2 failed");
		}
		close(shell->exec->infile);
		unlink(shell->cmd->last_file);
		free(shell->cmd->last_file);
	}
	else
		unlink(file);
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
