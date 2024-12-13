/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:23:35 by witong            #+#    #+#             */
/*   Updated: 2024/12/13 10:30:02 by witong           ###   ########.fr       */
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
