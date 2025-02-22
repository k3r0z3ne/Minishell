/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:34:31 by witong            #+#    #+#             */
/*   Updated: 2025/02/22 12:57:29 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_command(t_shell *shell)
{
	int	i;

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

	if (!shell || !shell->token || !shell->token->next)
		return ;
	if (shell->token->type == HEREDOC)
	{
		shell->cmd->limiter[shell->cmd->i_hd] \
			= ft_strdup_track(shell, shell->token->next->value);
		if (shell->token->next->type == SINGLEQ
			|| shell->token->next->type == DOUBLEQ)
			shell->cmd->is_quote = true;
		shell->cmd->i_hd++;
		shell->cmd->limiter[shell->cmd->i_hd] = NULL;
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
	t_cmd	*new_cmd;

	if (!shell || !shell->token)
		return ;
	new_cmd = init_cmd(shell, shell->token);
	if (!new_cmd)
		return ;
	new_cmd->prev = shell->cmd;
	shell->cmd->next = new_cmd;
	shell->cmd = new_cmd;
	shell->exec->cmd_count++;
	shell->token = shell->token->next;
}

static void	parse_tokens(t_shell *shell)
{
	while (shell->token && shell->token->type != END)
	{
		if (parser_error(&shell->token))
		{
			unexpected_token(shell, &shell->token);
			shell->cmd = NULL;
			return ;
		}
		if (shell->token->type == PIPE)
		{
			end_redir(shell);
			parse_pipe(shell);
		}
		if (is_redirection2(shell->token->type) && shell->token->next \
				&& is_word(shell->token->next->type))
			parse_redirs(shell);
		else if (is_word(shell->token->type))
			parse_command(shell);
		else
			shell->token = shell->token->next;
	}
	end_redir(shell);
}

void	parser(t_shell *shell)
{
	t_cmd	*head;

	if (!shell || !shell->token || !shell->token->value)
		return ;
	head = init_cmd(shell, shell->token);
	if (!head)
		return ;
	shell->cmd = head;
	shell->exec = init_exec(shell);
	if (!shell->exec)
		return ;
	parse_tokens(shell);
	if (shell->cmd)
	{
		shell->cmd = head;
		shell->cmd->i_hd = 0;
	}
	if (!validate_command(shell))
		return ;
}
