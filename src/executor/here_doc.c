/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:39:36 by arotondo          #+#    #+#             */
/*   Updated: 2025/03/03 17:24:29 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	iter_heredoc(t_shell *shell)
{
	t_redir	*tmp;

	shell->exec->tty_fd0 = dup(STDIN_FILENO);
	tmp = shell->cmd->redirs;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			shell->cmd->redirs = tmp;
			while (shell->cmd->redirs->type == HEREDOC)
			{
				if (shell->cmd->i_hd < shell->cmd->hd_count && \
					shell->cmd->loop_status != 2)
					process_heredoc(shell);
				shell->cmd->redirs = shell->cmd->redirs->next;
			}
			tmp = shell->cmd->redirs;
			if (shell->cmd->i_hd == shell->cmd->hd_count)
				break ;
			else if (shell->cmd->loop_status == 2)
				break ;
		}
		tmp = tmp->next;
	}
	return (shell->cmd->loop_status);
}

void	process_heredoc(t_shell *shell)
{
	char	*file_name;
	char	*idx_tmp;

	idx_tmp = ft_itoa(shell->cmd->i_hd);
	file_name = ft_strjoin2(".heredoc_", idx_tmp);
	free(idx_tmp);
	shell->exec->infile = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (shell->exec->infile < 0)
		err_message(shell, file_name, NULL, NULL);
	if (shell->cmd->last_file)
		free(shell->cmd->last_file);
	shell->cmd->last_file = ft_strdup(file_name);
	free(file_name);
	shell->cmd->loop_status = loop_heredoc(shell);
	shell->cmd->i_hd++;
	if (shell->cmd->loop_status == 2)
	{
		close(shell->exec->infile);
		unlink(shell->cmd->last_file);
		free(shell->cmd->last_file);
		shell->cmd->last_file = NULL;
		return ;
	}
	close(shell->exec->infile);
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
		if (status > 0)
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
		if (shell->cmd->i_hd == shell->cmd->hd_count)
		{
			shell->exec->infile = open(shell->cmd->last_file, 00, 0664);
			if (shell->exec->infile < 0)
				err_message(shell, shell->cmd->last_file, NULL, NULL);
			if (dup2(shell->exec->infile, STDIN_FILENO) < 0)
				err_message(shell, shell->cmd->last_file, NULL, NULL);
			close(shell->exec->infile);
		}
	}
	unlink(file);
	free(shell->cmd->last_file);
	shell->cmd->last_file = NULL;
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
