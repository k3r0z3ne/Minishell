/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_illegal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:17 by witong            #+#    #+#             */
/*   Updated: 2025/02/03 12:29:46 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_illegal_single(char c)
{
	if (c == '\\' || c == ';' || c == '(' || c == ')'
			|| c == '&' || c == '#' || c == '*' || c == '`'
			|| c == '{' || c == '}')
		return (1);
	return (0);
}

int	is_illegal_double(char c1, char c2)
{
	if ((c1 == '&' && c2 == '&') || (c1 == '|' && c2 == '|') || (c1 == '$' && c2 == '$'))
		return (1);
	return (0);
}
void	handle_illegal_single(char c, t_lexer *lexer)
{
	ft_putstr_fd("lexer: syntax error near unexpected token '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	lexer->error = 1;
	lexer->i++;
}

void	handle_illegal_double(char c1, char c2, t_lexer *lexer)
{
	ft_putstr_fd("lexer: syntax error near unexpected token '", 2);
	ft_putchar_fd(c1, 2);
	ft_putchar_fd(c2, 2);
	ft_putstr_fd("'\n", 2);
	lexer->error = 1;
	lexer->i += 2;
}

void	check_illegal(char *line, t_lexer *lexer)
{
	while (line[lexer->i])
	{
		if (line[lexer->i + 1] && is_illegal_double(line[lexer->i], line[lexer->i + 1]))
		{
			handle_illegal_double(line[lexer->i], line[lexer->i + 1], lexer);
			break ;
		}
		else if (is_illegal_single(line[lexer->i]))
		{
			handle_illegal_single(line[lexer->i], lexer);
			break ;
		}
		lexer->i++;
	}
	lexer->i = 0;
}
