/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:58:00 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/14 15:10:58 by witong           ###   ########.fr       */
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

	idx_tmp = ft_itoa(shell->cmd->i_hd);
	file_name = ft_strjoin2(".heredoc_", idx_tmp);
	free(idx_tmp);
	shell->exec->infile = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (shell->exec->infile < 0)
		err_exit("error opening file");
	if (shell->cmd->last_file)
		free(shell->cmd->last_file);
	shell->cmd->last_file = file_name;
	loop_heredoc(shell);
	shell->cmd->i_hd++;
	close(shell->exec->infile);
	redir_heredoc(shell, file_name);
}

void	loop_heredoc(t_shell *shell)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		write(0, "> ", 3);
		line = get_next_line(0);
		if (g_signal)
		{
			g_signal = 0;
			close(shell->exec->infile);
			shell->exec->infile = -1;
			break;
		}
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end-of-file '", 2);
			ft_putstr_fd(shell->cmd->limiter[shell->cmd->i_hd], 2);
			ft_putstr_fd("'\n", 2);
			break ;
		}
		fprintf(stderr, "limiter[%d] = %s\n", shell->cmd->i_hd, shell->cmd->limiter[shell->cmd->i_hd]);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, shell->cmd->limiter[shell->cmd->i_hd]) == 0)
		{
			free(line);
			break;
		}
		if (shell->cmd->is_quote == false)
		{
			tmp = expand_heredoc(shell, line);
			free(line);
			line = tmp;
		}
		ft_putendl_fd(line, shell->exec->infile);
	}
	get_next_line(-1);
}

void	redir_heredoc(t_shell *shell, char *file)
{
	if (shell->cmd->i_hd == shell->cmd->hd_count)
	{
		if (shell->exec->cmd_count)
		{
			if (shell->cmd->hd_count)
				shell->exec->infile = open(shell->cmd->last_file, O_RDONLY, 0664);
			if (shell->exec->infile < 0)
				err_exit("error opening file");
			if (dup2(shell->exec->infile, STDIN_FILENO) < 0)
				err_exit("dup2 failed");
		}
		close(shell->exec->infile);
		unlink(shell->cmd->last_file);
		free(shell->cmd->last_file);
		get_next_line(-1);
	}
	else
	{
		unlink(file);
		get_next_line(-1);
	}
}
