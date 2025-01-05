/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:34:31 by witong            #+#    #+#             */
/*   Updated: 2025/01/05 16:00:46 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_command(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->cmd->full_cmd[i])
		i++;
	shell->cmd->full_cmd[i] = ft_strdup(shell->token->value);
	i++;
	shell->cmd->full_cmd[i] = NULL;
}

static void	parse_redirs(t_shell *shell)
{
	t_redir	*new_redir;

	new_redir = create_redir(shell->token);
	if (!new_redir)
		return ;
	redir_add_back(&shell->cmd->redirs, new_redir);
	shell->token = shell->token->next;
}

static void	parse_pipe(t_shell *shell)
{
	shell->cmd->next = init_cmd(shell->token);
	if (!shell->cmd->next)
		return ;
	shell->cmd = shell->cmd->next;
}

static void	parse_tokens(t_shell *shell)
{
	while (shell->token && shell->token->type != END)
	{
		if (parser_error(&shell->token))
		{
			unexpected_token(&shell->token);
			free_cmd(&shell->cmd);
			shell->cmd = NULL;
			break ;
		}
		if (shell->token->type == DOUBLEQ || shell->token->type == DOLLAR)
			expander(shell, shell->token);
		if (shell->token->type == PIPE)
			parse_pipe(shell);
		if (is_redirection2(shell->token->type) && shell->token->next
				&& is_word(shell->token->next->type))
			parse_redirs(shell);
		if (is_word(shell->token->type))
			parse_command(shell);
		shell->token = shell->token->next;
	}
}

void	parser(t_shell *shell)
{
	if (!shell || !shell->token || !shell->token->value)
		return ;
	shell->cmd = init_cmd(shell->token);
	if (!shell->cmd)
		return ;
	parse_tokens(shell);
	if (!validate_command(shell))
	{
		free_cmd(&shell->cmd);
		shell->cmd = NULL;
		return ;
	}
}
