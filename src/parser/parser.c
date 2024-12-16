/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:34:31 by witong            #+#    #+#             */
/*   Updated: 2024/12/16 16:44:49 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	parse_redirs(t_token **tokens, t_cmd **cmd)
{
	(*cmd)->redirs = ft_calloc(1, sizeof(t_redir));
	if (!(*cmd)->redirs)
		return ;
	(*cmd)->redirs->type = (*tokens)->type;
	(*cmd)->redirs->file = ft_strdup((*tokens)->value);

	(*cmd) = (*cmd)->next;
	(*tokens) = (*tokens)->next;
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
		else if (is_redirection2((*tokens)->type) && (*cmd)->redirs)
			parse_redirs(tokens, cmd);
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
