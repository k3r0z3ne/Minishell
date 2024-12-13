/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:34:31 by witong            #+#    #+#             */
/*   Updated: 2024/12/13 15:58:12 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*init_cmd(t_token *tokens)
{
	t_cmd *cmd;
	int	i;
	int	size;

	if (!tokens)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	size = token_len(tokens);
	cmd->full_cmd = (char **)malloc(sizeof(char *) * size);
	if (!cmd->full_cmd)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	while (i < size)
		cmd->full_cmd[i++] = NULL;
	cmd->redirs = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);

}

// void	parse_redirs(t_token **tokens, t_cmd *cmd)
// {
// 	if (!tokens || !(*token))
// 		return ;
// 	if ((*tokens)->type == REDIRIN)
// 		parse_redirin(tokens, cmd);
// 	else if ((*tokens)->type == REDIROUT)
// 		parse_redirout(tokens, cmd);
// 	else if ((*tokens)->type == APPEND)
// 		parse_append(tokens, cmd);
// 	else if ((*tokens)->type == HEREDOC)
// 		parse_heredoc(tokens, cmd);
// 	*tokens = (*tokens)->next;
// }

void	parse_command(t_token **tokens, t_cmd **cmd)
{
	int i;

	if (!tokens || !(*tokens) || !(*tokens)->value)
		return ;
	i = 0;
	while ((*cmd)->full_cmd[i])
		i++;
	(*cmd)->full_cmd[i] = ft_strdup((*tokens)->value);
	i++;
	(*cmd)->full_cmd[i] = NULL;
}

t_cmd	*parser(t_token *tokens)
{
	t_token	*current;
	t_cmd	*cmd;
	t_cmd	*head;

	if(!tokens || !tokens->value)
		return(NULL);
	current = tokens;
	cmd = init_cmd(tokens);
	if (!cmd)
		return (NULL);
	head = cmd;
	while (current && current->type != END)
	{
		if (is_word(current->type))
			parse_command(&current, &cmd);
		// else if (is_redirection2(current->type))
		// {
		// 	parse_redirs(&current, cmd);
		// 	current = current->next;
		// }
		else if (current->type == PIPE)
		{
			cmd->next = init_cmd(current);
			if(!cmd->next)
				return (NULL);
			cmd = cmd->next;
		}
		// else
		// 	//error
		current = current->next;
	}
	return (head);
}
