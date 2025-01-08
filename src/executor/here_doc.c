/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:58:00 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/08 12:20:28 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	handle_here_doc(t_shell *shell, t_cmd *cmd)
{
	char	*line;
	(void)shell;

	while (1)
	{
		write(0, "> ", 3);
		line = get_next_line(0);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, cmd->limiter) == 0)
		{
			free(line);
			break ;
		}
		// if (cmd->is_quote == false)
		// 	line = expand_heredoc(line);
		ft_putendl_fd(line, cmd->infile);
		free(line);
	}
	get_next_line(-1);
	close (cmd->infile);
}
