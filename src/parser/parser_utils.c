/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:23:35 by witong            #+#    #+#             */
/*   Updated: 2024/12/13 16:08:00 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_word(t_tok_type type)
{
	return (type == WORD || type == SINGLEQ || type == DOUBLEQ);
}

int	is_redirection2(t_tok_type type)
{
	return (type == REDIRIN || type == REDIROUT || type == HEREDOC || type == APPEND);
}
int	token_len(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

void	print_table(t_cmd *cmds)
{
	int	i;
	int	j;
	t_cmd	*current;

	j = 0;
	current = cmds;
	while (current)
	{
		i = 0;
		printf("Command[%d]:\n", j);
		while (current->full_cmd[i])
		{
			printf("  Arg[%d]: %s\n", i, current->full_cmd[i]);
			i++;
		}
		current = current->next;
		j++;
	}
}
