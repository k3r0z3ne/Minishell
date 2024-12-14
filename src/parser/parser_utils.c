/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:23:35 by witong            #+#    #+#             */
/*   Updated: 2024/12/14 11:26:13 by witong           ###   ########.fr       */
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
		printf("  Arg[%d]: %s\n", i, current->full_cmd[i]);
		current = current->next;
		j++;
	}
}
void unexpected_token(t_token **tokens)
{
	ft_putstr_fd("parser: syntax error near unexpected token '", 2);
	ft_putstr_fd((*tokens)->value, 2);
	ft_putstr_fd("'\n", 2);
}
