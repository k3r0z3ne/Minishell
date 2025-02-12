/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:58:00 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/12 10:52:46 by arotondo         ###   ########.fr       */
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
	char	*last_file;

	last_file = NULL;
	file_name = ft_strjoin2(".heredoc_", ft_itoa(shell->cmd->i_hd));
	shell->exec->infile = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (shell->exec->infile < 0)
		err_exit("error opening file");
	if (last_file)
		free(last_file);
	last_file = file_name;
	loop_heredoc(shell);
	shell->cmd->i_hd++;
	redir_heredoc(shell, last_file, file_name);
	get_next_line(-1);
}

void	loop_heredoc(t_shell *shell)
{
	char	*line;

	while (1)
	{
		write(0, "> ", 3);
		line = get_next_line(0);
		if (!line)
			break ;
		if (shell->cmd->is_quote == false)
			line = expand_heredoc(shell, line);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, shell->cmd->limiter[shell->cmd->i_hd]) == 0)
			break ;
		ft_putendl_fd(line, shell->exec->infile);
	}
}

void	redir_heredoc(t_shell *shell, char *last, char *file)
{
	if (shell->cmd->i_hd == shell->cmd->hd_count)
	{
		if (shell->cmd->hd_count)
			shell->exec->infile = open(last, O_RDONLY, 0664);
		if (shell->exec->infile < 0)
			err_exit("error opening file");
		if (dup2(shell->exec->infile, STDIN_FILENO) < 0)
			err_exit("dup2z failed");
		close(shell->exec->infile);
		unlink(last);
		free(last);
	}
	else
		unlink(file);
}
