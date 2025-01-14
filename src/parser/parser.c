/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:34:31 by witong            #+#    #+#             */
/*   Updated: 2025/01/14 18:36:59 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_command(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->cmd->full_cmd[i])
		i++;
	shell->cmd->full_cmd[i] = ft_strdup_track(shell, shell->token->value);
	i++;
	shell->cmd->full_cmd[i] = NULL;
	shell->token = shell->token->next;
}

static void	parse_redirs(t_shell *shell)
{
	t_redir	*new_redir;

	if (!shell->token || !shell->token->next)
		return;
	if (shell->token->type == HEREDOC)
	{
		shell->cmd->limiter = shell->token->next->value;
		if (shell->token->next->type == SINGLEQ
				|| shell->token->next->type == DOUBLEQ)
			shell->cmd->is_quote = true;
	}
	new_redir = create_redir(shell, shell->token);
	if (!new_redir)
		return ;
	redir_add_back(&shell->cmd->redirs, new_redir);
	shell->token = shell->token->next;
	if (shell->token)
		shell->token = shell->token->next;
}

static void	parse_pipe(t_shell *shell)
{
	t_cmd *new_cmd;

	new_cmd = init_cmd(shell, shell->token);
	if (!new_cmd)
		return ;
	new_cmd->prev = shell->cmd;
	shell->cmd->next = new_cmd;
	shell->cmd = new_cmd;
	shell->token = shell->token->next;
}

static void	parse_tokens(t_shell *shell)
{
	while (shell->token && shell->token->type != END)
	{
		if (parser_error(&shell->token))
		{
			unexpected_token(&shell->token);
			shell->cmd = NULL;
			break ;
		}
		if (shell->token->type == PIPE)
			parse_pipe(shell);
		if (is_redirection2(shell->token->type) && shell->token->next
				&& shell->token->next->type == WORD)
			parse_redirs(shell);
		else if (shell->token->type == WORD)
			parse_command(shell);
		else
			shell->token = shell->token->next;
	}
}

void	parser(t_shell *shell)
{
	t_cmd *head;

	if (!shell || !shell->token || !shell->token->value)
		return ;
	head = init_cmd(shell, shell->token);
	if (!head)
		return ;
	shell->cmd = head;
	parse_tokens(shell);
	if (shell->cmd)
		shell->cmd = head;
	if (!validate_command(shell))
		return ;
}
