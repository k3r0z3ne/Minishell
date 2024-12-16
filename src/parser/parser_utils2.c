/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:25:07 by witong            #+#    #+#             */
/*   Updated: 2024/12/16 14:18:12 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_table(t_cmd *cmd)
{
	int	i;
	int	j;
	t_cmd	*current;

	j = 0;
	current = cmd;
	while (current)
	{
		i = 0;
		printf("Command[%d]:\n", j);
		while (current->full_cmd[i])
		{
			printf("  Arg[%d]: %s\n", i, current->full_cmd[i]);
			i++;
		}
		printf("  Arg[%d]: %s\n", i, current->full_cmd[i]);
		current = current->next;
		j++;
	}
}

void	print_redirs(t_cmd *cmd)
{
	int	j;
	t_cmd	*current;
	t_redir	*redir;

	j = 0;
	current = cmd;
	while (current)
	{
		printf("Command[%d] Redirections:\n", j);
		redir = current->redirs;
		while (redir)
		{
			printf("  Redir Type: %d, File: %s\n", redir->type, redir->file);
			redir = redir->next;
		}
		current = current->next;
		j++;
	}
}
