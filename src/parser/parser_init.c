/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:48:05 by witong            #+#    #+#             */
/*   Updated: 2024/12/17 12:17:46 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **malloc_full_cmd(int size)
{
	char	**full_cmd;
	int	i;

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
	int	size;

	if (!tokens)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	size = token_len(tokens);
	cmd->full_cmd = malloc_full_cmd(size);
	cmd->redirs = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}
