/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:58:00 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/11 17:23:21 by arotondo         ###   ########.fr       */
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

// void	loop_here_doc(t_shell *shell)
// {
// 	count_fds(shell);
// 	fprintf(stderr, "nb of hd = %d\n", shell->cmd->hd_count);
// 	while (shell->cmd->hd_count)
// 	{
// 		shell->exec->infile = open(".tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0664);
// 		if (shell->exec->infile < 0)
// 			err_exit("error opening file");
// 		fprintf(stderr, "infile open ?\n");
// 		shell->cmd->hd_count--;
// 		close(shell->exec->infile);
// 	}
// }

void	process_heredoc(t_shell *shell)
{
	char	*heredoc;
	char	*line;
	int		i;

	i = 0;
	while (i < shell->cmd->hd_count - 1)
	{
		heredoc = ft_strjoin_track(shell, ".heredoc_", ft_itoa(i));
		fprintf(stderr, "heredoc = %s\n", heredoc);
		fprintf(stderr, "limiter[%d] = %s\n", i, shell->cmd->limiter[i]);
		shell->exec->infile = open(heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (shell->exec->infile < 0)
			err_exit("error opening file");
		free(heredoc);
		i++;
	}
	i = 0;
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
		fprintf(stderr, "limiter[i] = %s\n", shell->cmd->limiter[i]);
		if (ft_strcmp(line, shell->cmd->limiter[i]) == 0)
			break ;
		ft_putendl_fd(line, shell->exec->infile);
		i++;
	}
	if (i == shell->cmd->hd_count - 1)
	{
		if (shell->cmd->hd_count)
			shell->exec->infile = open(heredoc, O_RDONLY, 0664);
		if (shell->exec->infile < 0)
			err_exit("error opening file");
	}
	get_next_line(-1);
	unlink(heredoc);
}
