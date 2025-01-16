/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:58:00 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/16 17:18:23 by xenon            ###   ########.fr       */
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

void	handle_here_doc(t_shell *shell)
{
	char	*line;

	shell->cmd->flag_hd = true;
	shell->exec->infile = open(".tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (shell->exec->infile < 0)
		return ;
	while (1)
	{
		write(0, "> ", 3);
		line = get_next_line(0);
		if (!line)
			break ;
		printf("line %p\n", line);
		if (shell->cmd->is_quote == false)
			line = expand_heredoc(shell, line);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, shell->cmd->limiter) == 0)
			break ;
		ft_putendl_fd(line, shell->exec->infile);
	}
	get_next_line(-1);
	// close (cmd->infile);
}
