#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_clean
{
	void	*ptr;
	struct s_clean	*next;
}		t_clean;

/* clean_up */
void	free_array(char **array);
void	free_redir(t_redir **redir);
void	free_redirs(t_redir **redirs);
void	free_cmd(t_cmd **cmd);
void	*tracked_malloc(t_shell *shell, size_t size);
void	cleanup_all(t_shell *shell);

/* global utils */
int		ft_isupper(int c);
int		count_line(char **array);
char	**arraydup(char **array);
char	*ft_strdup_track(t_shell *shell, char *src);
char	*ft_substr_track(t_shell *shell, char const *s, unsigned int start, size_t len);

/* init */
void	init_shell(t_shell *shell, int argc, char **argv, char **envp);

#endif
