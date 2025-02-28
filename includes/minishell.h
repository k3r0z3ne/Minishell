/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:20:59 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/28 14:22:32 by arotondo         ###   ########.fr       */
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
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "lexer.h"
# include "parser.h"
# include "expand.h"
# include "exec.h"
# include "builtins.h"
# include "utils.h"

typedef struct s_shell			t_shell;
typedef struct s_token			t_token;
typedef enum e_type				t_type;
typedef struct s_clean			t_clean;

/* redirections structure */
typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*prev;
}			t_redir;

/* commands chained list */
typedef struct s_cmd
{
	char			**full_cmd;
	bool			is_quote;
	bool			flag_hd;
	int				i_hd;
	int				hd_count;
	int				loop_status;
	int				cmd_len;
	int				in_count;
	char			*last_file;
	char			**limiter;
	struct s_redir	*redirs;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}			t_cmd;

typedef struct s_exec
{
	int		infile;
	int		outfile;
	int		cmd_count;
	int		builtin_less;
	int		pipe[2];
	int		old_pipe;
	int		tty_fd0;
	int		tty_fd1;
	pid_t	*pids;
	bool	last_cmd;
	bool	if_pipe;
}			t_exec;

/* global data structure */
typedef struct s_shell
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*input;
	int		last_status;
	t_token	*token;
	t_cmd	*cmd;
	t_exec	*exec;
	t_clean	*clean;
}			t_shell;

extern volatile sig_atomic_t	g_signal;

#endif
