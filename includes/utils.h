#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_clean
{
	void			*ptr;
	struct	s_clean	*next;
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
char	*ft_substr_track(t_shell *shell, char const *s, unsigned int start, size_t len);
char	*ft_strjoin_track(t_shell *shell, const char *s1, const char *s2);
void	*tracked_malloc(t_shell *shell, size_t size);
void	cleanup_all(t_shell *shell);

/* init */
void	init_shell(t_shell *shell, int argc, char **argv, char **envp);
void	init_pids(t_shell *shell);

/* signals */
void	setup_signals(void);
void	ignore_ctrl_c(void);
void	activate_ctrl_c(void);
void	activate_ctrl_backslash(void);

/* error */
int		err_exit(char *err_message);
int		err_return(char *err_message);

#endif
