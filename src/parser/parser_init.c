/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:48:05 by witong            #+#    #+#             */
/*   Updated: 2025/01/29 13:06:15 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**malloc_full_cmd(t_shell *shell, int size)
{
	char	**full_cmd;
	int		i;

	full_cmd = (char **)tracked_malloc(shell, sizeof(char *) * (size + 1));
	if (!full_cmd)
		return (NULL);
	i = 0;
	while (i < size)
		full_cmd[i++] = NULL;
	return (full_cmd);
}

int	how_much_cmd(t_shell *shell)
{
	t_shell	tmp;
	int		builtins;
	int		ret;

	builtins = 0;
	tmp = *shell;
	while ((&tmp)->cmd)
	{
		if (is_builtin(&tmp) == true)
			builtins++;
		(&tmp)->cmd = (&tmp)->cmd->next;
	}
	// printf("cmd->count = %d\n", shell->exec->cmd_count);
	// printf("nb builtins = %d\n", builtins);
	ret = shell->exec->cmd_count - builtins;
	// printf("ret = %d\n", ret);
	return (ret);
}

t_exec	*init_exec(t_shell *shell)
{
	t_exec	*exec;

	exec = tracked_malloc(shell, sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->infile = 0;
	exec->outfile = 0;
	exec->exit_status = 0;
	exec->cmd_count = 1;
	exec->last_cmd = false;
	return (exec);
}

t_cmd	*init_cmd(t_shell *shell, t_token *tokens)
{
	t_cmd	*cmd;
	int		size;

	if (!shell || !tokens)
		return (NULL);
	cmd = tracked_malloc(shell, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	size = token_len(tokens);
	cmd->full_cmd = malloc_full_cmd(shell, size);
	cmd->is_quote = false;
	cmd->flag_hd = false;
	cmd->limiter = NULL;
	cmd->in_count = 0;
	cmd->out_count = 0;
	cmd->hd_count = 0;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}
