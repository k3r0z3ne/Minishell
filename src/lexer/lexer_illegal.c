/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_illegal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:17 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 16:54:51 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_illegal_single(char c)
{
	if (c == '\\' || c == ';' || c == '(' || c == ')'
			|| c == '&' || c == '#' || c == '*' || c == '`'
			|| c == '[' || c == ']' || c == '{' || c == '}')
		return (1);
	return (0);
}

int	is_illegal_double(char c1, char c2)
{
	if ((c1 == '&' && c2 == '&') || (c1 == '|' && c2 == '|') || (c1 == '$' && c2 == '$'))
		return (1);
	return (0);
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
	while (line[state->i])
	{
		if (line[state->i + 1] && is_illegal_double(line[state->i], line[state->i + 1]))
		{
			handle_illegal_double(line[state->i], line[state->i + 1], state);
			break ;
		}
		else if (is_illegal_single(line[state->i]))
		{
			handle_illegal_single(line[state->i], state);
			break ;
		}
		state->i++;
	}
	state->i = 0;
}
