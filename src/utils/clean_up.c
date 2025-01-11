// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   clean_up.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/12/16 17:15:56 by arotondo          #+#    #+#             */
// /*   Updated: 2025/01/09 13:11:52 by witong           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **array)
{
	int	i;
	int	size;

	if (!array || !*array)
		return ;
	i = 0;
	size = count_line(array);
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

// void	free_redir(t_redir **redir)
// {
// 	if (!redir || !*redir)
// 		return ;
// 	if ((*redir)->file)
// 		free((*redir)->file);
// 	if ((*redir))
// 		free(*redir);
// 	*redir = NULL;
// }

// void	free_redirs(t_redir **redirs)
// {
// 	t_redir	*current;
// 	t_redir	*next;

// 	if (!redirs || !*redirs)
// 		return ;
// 	current = *redirs;
// 	while (current)
// 	{
// 		next = current->next;
// 		free_redir(&current);
// 		current = next;
// 	}
// 	*redirs = NULL;
// }

// void	free_cmd(t_cmd **cmd)
// {
// 	t_cmd	*current;
// 	t_cmd	*next;

// 	if (!cmd || !*cmd)
// 		return ;

// 	current = *cmd;
// 	while (current && current->prev)
// 		current = current->prev;
// 	while (current)
// 	{
// 		next = current->next;
// 		if (current->full_cmd)
// 			free_array(current->full_cmd);
// 		if (current->redirs)
// 			free_redirs(&current->redirs);
// 		if (current->pids)
// 			free(current->pids);
// 		free(current);
// 		current = next;
// 	}
// 	*cmd = NULL;
// }
