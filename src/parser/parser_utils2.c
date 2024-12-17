/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:25:07 by witong            #+#    #+#             */
/*   Updated: 2024/12/17 12:19:45 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir	*create_redir(t_token *tokens)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = tokens->type;
	new_redir->file = ft_strdup(tokens->next->value);
	if (!new_redir->file)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->next = NULL;
	new_redir->prev = NULL;
	return (new_redir);
}

void	redir_add_back(t_redir **redirs, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!redirs || !new_redir)
		return ;
	if (!*redirs)
	{
		*redirs = new_redir;
		return ;
	}
	tmp = *redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
	new_redir->prev = tmp;
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
