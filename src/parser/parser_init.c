/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:48:05 by witong            #+#    #+#             */
/*   Updated: 2025/02/19 11:00:14 by arotondo         ###   ########.fr       */
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

	if (!(shell->cmd->full_cmd[0]))
		return (0);
	builtins = 0;
	tmp = *shell;
	ret = 0;
	if (!(&tmp)->cmd->full_cmd[0])
		return (ret);
	while ((&tmp)->cmd)
	{
		if (is_builtin(&tmp) == true)
			builtins++;
		(&tmp)->cmd = (&tmp)->cmd->next;
	}
	ret = shell->exec->cmd_count - builtins;
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
	exec->cmd_count = 1;
	exec->last_cmd = false;
	exec->old_pipe = -1;
	exec->builtin_less = 0;
	exec->if_pipe = false;
	return (exec);
}

t_cmd	*init_cmd(t_shell *shell, t_token *tokens)
{
	t_cmd	*cmd;

	if (!shell || !tokens)
		return (NULL);
	cmd = tracked_malloc(shell, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->full_cmd = malloc_full_cmd(shell, token_len(tokens));
	cmd->is_quote = false;
	cmd->flag_hd = false;
	cmd->i_hd = 0;
	cmd->in_count = 0;
	cmd->out_count = 0;
	cmd->last_file = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->hd_count = count_heredoc(shell);
	if (cmd->hd_count > 0)
		cmd->limiter = (char **)tracked_malloc(shell, sizeof(char *) * \
			(cmd->hd_count + 1));
	else
		cmd->limiter = NULL;
	return (cmd);
}
