/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:48:05 by witong            #+#    #+#             */
/*   Updated: 2024/12/30 16:54:33 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**malloc_full_cmd(int size)
{
	char	**full_cmd;
	int		i;

	full_cmd = (char **)malloc(sizeof(char *) * size);
	if (!full_cmd)
		return (NULL);
	i = 0;
	while (i < size)
		full_cmd[i++] = NULL;
	return (full_cmd);
}

t_cmd	*init_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	int		size;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	// printf("cmd in init_cmd : %p\n", cmd);
	size = token_len(tokens);
	cmd->full_cmd = malloc_full_cmd(size);
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->heredoc = -1;
	cmd->append = -1;
	// *cmd->pipe = -1;
	cmd->pids = malloc(sizeof(pid_t) * size);
	if (!cmd->pids)
		return (NULL);
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
