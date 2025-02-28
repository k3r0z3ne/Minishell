/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arotondo <arotondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:03:58 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/28 14:18:46 by arotondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_clean
{
	void			*ptr;
	struct s_clean	*next;
}			t_clean;

/* global utils */
int		ft_isupper(int c);
int		count_line(char **array);

/* env_utils */
char	*ft_strjoin2(const char *s1, const char *s2);
char	**mini_env(void);
char	*ft_getenv(const char *name, char **envp);
char	**arraydup(char **array);
void	free_array(char **array);

/* gc */
char	*ft_strdup_track(t_shell *shell, char *src);
char	*ft_substr_track(t_shell *shell, char *s, unsigned int start, size_t n);
char	*ft_strjoin_track(t_shell *shell, const char *s1, const char *s2);
void	*tracked_malloc(t_shell *shell, size_t size);
void	cleanup_all(t_shell *shell);

/* init */
void	init_shell(t_shell *shell, int argc, char **argv, char **envp);
void	init_pids(t_shell *shell);

/* signals */
void	setup_signals(t_shell *shell);
void	setup_child_signals(t_shell *shell);
void	ignore_ctrl_c(t_shell *shell);

/* error */
void	close_pipes(t_shell *shell);
void	err_message(t_shell *shell, char *cmd, char *arg, char *mess);
void	err_message2(char *cmd, char *arg, char *mess);

#endif
