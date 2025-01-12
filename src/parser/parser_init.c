/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:48:05 by witong            #+#    #+#             */
/*   Updated: 2025/01/12 16:13:56 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**malloc_full_cmd(t_shell *shell, int size)
{
	char	**full_cmd;
	int		i;

	full_cmd = (char **)tracked_malloc(shell, sizeof(char *) * size);
	if (!full_cmd)
		return (NULL);
	i = 0;
	while (i < size)
		full_cmd[i++] = NULL;
	return (full_cmd);
}

t_cmd	*init_cmd(t_shell *shell, t_token *tokens)
{
	t_cmd	*cmd;
	int		size;

	cmd = tracked_malloc(shell, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	size = token_len(tokens);
	cmd->full_cmd = malloc_full_cmd(shell, size);
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->is_quote = false;
	cmd->flag_hd = false;
	cmd->limiter = NULL;
	// *cmd->pipe = NULL;
	cmd->pids = malloc(sizeof(pid_t) * shell->cmd_count);
	if (!cmd->pids)
		return (NULL);
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
