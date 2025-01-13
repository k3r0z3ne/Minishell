/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:33:27 by witong            #+#    #+#             */
/*   Updated: 2025/01/13 14:36:12 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/lexer.h"

void	append_chars(t_shell *shell, t_lexer *state, char *line)
{
	(void)shell;

	if (line[state->i] == '\'' || line[state->i] == '"')
	{
		if(state->quote == '\0')
			state->quote = line[state->i];
		else if (line[state->i] == state->quote)
			state->quote = '\0';
	}
	state->expand_input[state->j] = line[state->i];
	state->i++;
	state->j++;
}

char	*add_spaces(t_shell *shell, t_lexer *state, char *line)
{
	(void)shell;
	state->i = 0;
	state->j = 0;
	while (line[state->i])
	{
		// if ((line[state->i] == '<' && line[state->i + 1] == '<')
		// 		|| (line[state->i] == '>' && line[state->i] == '>'))
		// 	handle_double_ops_space(shell, state, line);
		// if (line[state->i] == '|' || line[state->i] == '<' || line[state->i] == '>')
		// 	handle_single_ops_space(shell, state, line);
		if (line[state->i] == '$' && !state->is_heredoc && state->quote !='\'')
			expand_lexer(shell, state, line);
		else
			append_chars(shell, state, line);
	}
	state->expand_input[state->j] = '\0';
	return (state->expand_input);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_shell shell;
// 	t_lexer state;
// 	char expand_input[20480];

// 	if(ac == 2)
// 	{
// 		char	*line = av[1];
// 		state.expand_input = expand_input;
// 		printf("line: %s\n", line);
// 		add_spaces(&shell, &state, line);
// 		printf("output: %s\n", state.expand_input);
// 		return (0);
// 	}
// 	return (1);
// }
