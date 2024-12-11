/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:51:58 by witong            #+#    #+#             */
/*   Updated: 2024/12/11 11:44:14 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

// lexer
typedef enum e_tok_type
{
	WORD,
	PIPE,
	SIMPLEQ,
	DOUBLEQ,
	DOLLAR,
	REDIRIN,
	REDIROUT,
	APPEND,
	HEREDOC,
	UNKNOWN,
	END,
}		t_tok_type;

typedef struct s_token
{
	t_tok_type type;
	char	*value;
	struct s_token *next;
}	t_token;

// lexer and utils
t_token	*lexer(char *line);
t_token	*create_token(t_tok_type type, char *value);
void token_add_back(t_token **list, t_token *new_token);
void print_tokens(t_token *token);
int	ft_isspace(char c);
int	is_special_char(char c);

// exec
// typedef struct	s_Command
// {
// 	int		_numberOfSimpleCmds;
// 	char	*_infile;
// 	char	*_outfile;
// 	char	*_errfile;
// 	t_SimpleCommand	**SimpleCommand;
// }				t_Command;

// typedef struct	s_SimpleCommand
// {
// 	int		_numberOfArgs;
// 	char	**_commands;
// }				t_SimpleCommand;

// typedef struct	s_shell
// {
// 	char	**argv;
// 	char	**envp;
// 	int		infile;
// 	int		outfile;
// 	int		nb_cmd;
// 	int		**pipe;
// 	pid_t	*pids;
// 	t_Command	*Commands;
// }				t_shell;

char *ft_getenv(const char *name, char **envp);

#endif
