/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:34:31 by witong            #+#    #+#             */
/*   Updated: 2024/12/13 11:28:48 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*init_cmd(void)
{

}

void	parse_redirs(t_token *token, t_cmd *cmd)
{
	
}

void	parse_command(t_token *token, t_cmd *cmd)
{
	int i;

	if (!token || !token->value)
		return ;
	i = 0;
	while (cmd->full_cmd[i])
		i++;
	cmd->full_cmd[i] = ft_strdup(token->value);
	i++;
	cmd->full_cmd[i] = NULL;
}

t_cmd	parser(t_token *tokens)
{
	t_token	*current;
	t_cmd	*cmd;
	t_cmd	*head;

	if(!tokens || !token->value)
		return(NULL);
	current = tokens;
	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	head = cmd;
	while (current && current->type != END)
	{
		if (is_word(current->type))
			parse_command(tokens, cmd);
		else if (is_redirection2(current->type))
		{
			parse_redirs(tokens, cmd);
			current = current->next;
		}
		else if (current->type == PIPE)
		{
			cmd = cmd->next;
			current = current->next;
		}
		else
			//error
		current = current->next;
	}
	return (head);
}
