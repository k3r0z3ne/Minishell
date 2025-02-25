/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_illegal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:53:17 by witong            #+#    #+#             */
/*   Updated: 2025/02/22 13:20:57 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_illegal_single(char c)
{
	if (c == '\\' || c == ';' || c == '(' || c == ')' \
		|| c == '&' || c == '#' || c == '*' || c == '`' \
		|| c == '{' || c == '}')
		return (1);
	return (0);
}

static int	is_illegal_double(char c1, char c2)
{
	if ((c1 == '&' && c2 == '&') || (c1 == '|' && c2 == '|') \
	|| (c1 == '$' && c2 == '$'))
		return (1);
	return (0);
}

static void	handle_illegal_single(char c, t_shell *shell, t_lexer *lexer)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	shell->last_status = 2;
	lexer->error = 1;
	lexer->i++;
}

static void	handle_illegal_double(char c1, char c2,
	t_shell *shell, t_lexer *lexer)
{
	ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
	ft_putchar_fd(c1, 2);
	ft_putchar_fd(c2, 2);
	ft_putstr_fd("'\n", 2);
	shell->last_status = 2;
	lexer->error = 1;
	lexer->i += 2;
}

void	check_illegal(char *line, t_shell *shell, t_lexer *lexer)
{
	while (line[lexer->i])
	{
		if (line[lexer->i + 1]
			&& is_illegal_double(line[lexer->i], line[lexer->i + 1]))
		{
			handle_illegal_double(line[lexer->i], \
			line[lexer->i + 1], shell, lexer);
			break ;
		}
		else if (is_illegal_single(line[lexer->i]))
		{
			handle_illegal_single(line[lexer->i], shell, lexer);
			break ;
		}
		lexer->i++;
	}
	lexer->i = 0;
}
