/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:20:28 by witong            #+#    #+#             */
/*   Updated: 2024/12/13 16:28:13 by witong           ###   ########.fr       */
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

#include "lexer.h"
#include "parser.h"

// Redirection struct
typedef struct s_redir
{
	t_tok_type	type;
	char	*file;
	struct s_redir *next;
}	t_redir;

// Command chained list
typedef struct s_cmd
{
	char	**full_cmd;
	struct s_redir	*redirs;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

# include "lexer.h"
# include "parser.h"

#endif
