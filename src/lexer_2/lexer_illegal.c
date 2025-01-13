/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_illegal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 01:23:10 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 12:03:49 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_illegal_single(char c)
{
	return (c == '\\' || c == ';' || c == '(' || c == ')' ||
		c == '&' || c == '#' || c == '*' || c == '`' ||
		c == '[' || c == ']' || c == '{' || c == '}');
}

int	is_illegal_double(char c1, char c2)
{
	return ((c1 == '&' && c2 == '&') || (c1 == '|' && c2 == '|') || (c1 == '$' && c2 == '$'));
}

void	handle_illegal_single(char c, t_lexer *state)
{
	ft_putstr_fd("lexer: syntax error near unexpected token '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	state->error = 1;
	state->i++;
}

void	handle_illegal_double(char c1, char c2, t_lexer *state)
{
	ft_putstr_fd("lexer: syntax error near unexpected token '", 2);
	ft_putchar_fd(c1, 2);
	ft_putchar_fd(c2, 2);
	ft_putstr_fd("'\n", 2);
	state->error = 1;
	state->i += 2;
}
void	check_illegal(char *line, t_lexer *state)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] && is_illegal_double(line[i], line[i + 1]))
		{
			handle_illegal_double(line[i], line[i + 1], state);
			break ;
		}
		else if (is_illegal_single(line[i]))
		{
			handle_illegal_single(line[i], state);
			break ;
		}
		i++;
	}
}
