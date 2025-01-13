/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:58:00 by arotondo          #+#    #+#             */
/*   Updated: 2025/01/13 13:52:40 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

char	*expand_heredoc(t_shell *shell, char *line)
{
	char	*result;

	if (!line)
		return (NULL);
	result = ft_strdup_track(shell, "");
	if (!result)
		return (NULL);
	process_expand_str(shell, &result, line);
	return (result);
}

void	handle_here_doc(t_shell *shell, t_cmd *cmd)
{
	char	*line;

	cmd->flag_hd = true;
	cmd->infile = open(".tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (cmd->infile < 0)
		return ;
	while (1)
	{
		write(0, "> ", 3);
		line = get_next_line(0);
		if (!line)
			break ;
		printf("line %p\n", line);
		if (cmd->is_quote == false)
			line = expand_heredoc(shell, line);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, cmd->limiter) == 0)
			break ;
		ft_putendl_fd(line, cmd->infile);
	}
	get_next_line(-1);
	// close (cmd->infile);
}
