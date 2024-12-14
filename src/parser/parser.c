/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:34:31 by witong            #+#    #+#             */
/*   Updated: 2024/12/14 14:52:05 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_cmd *parser(t_token *tokens)
{
	t_cmd *cmd;
	t_cmd *head;

	if (!tokens || !tokens->value)
		return (NULL);
	cmd = init_cmd(tokens);
	if (!cmd)
		return (NULL);
	head = cmd;
	parse_tokens(&tokens, &cmd);
	return (head);
}


void	parse_command(t_token **tokens, t_cmd **cmd)
{
	int i;

	i = 0;
	while ((*cmd)->full_cmd[i])
		i++;
	(*cmd)->full_cmd[i] = ft_strdup((*tokens)->value);
	i++;
	(*cmd)->full_cmd[i] = NULL;
}

void	parse_pipe(t_token **tokens, t_cmd **cmd)
{
	(*cmd)->next = init_cmd(*tokens);
	if (!(*cmd)->next)
		return;
	*cmd = (*cmd)->next;
}

void	parse_tokens(t_token **tokens, t_cmd **cmd)
{
	while (*tokens && (*tokens)->type != END)
	{
		if (parser_error(tokens))
			break;
		else if ((*tokens)->type == PIPE)
			parse_pipe(tokens, cmd);
		// else if (is_redirection2((*tokens)->type))
		// 	parse_redirs(tokens, cmd);
		else if (is_word((*tokens)->type))
			parse_command(tokens, cmd);
		else
		{
			unexpected_token(tokens);
			break;
		}
		*tokens = (*tokens)->next;
	}
}
