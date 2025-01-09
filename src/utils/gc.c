/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:12:07 by witong            #+#    #+#             */
/*   Updated: 2025/01/09 13:14:14 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*tracked_malloc(t_shell *shell, size_t size)
{
	void	*ptr;
	t_clean	*node;

	if (!shell || !size)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	node = (t_clean *)malloc(sizeof(t_clean));
	if (!node)
	{
		perror("Cleanup node creation failed");
		free(ptr);
		exit(EXIT_FAILURE);
	}
	node->ptr = ptr;
	node->next = shell->clean;
	shell->clean = node;
	return (ptr);
}

void	cleanup_all(t_shell *shell)
{
	t_clean	*current;
	t_clean	*next;

	current = shell->clean;
	while (current)
	{
		next = current->next;
		if (current->ptr)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		free(current);
		current = next;
	}
	shell->clean = NULL;
}

char	*ft_strdup_track(t_shell *shell, char *src)
{
	int		srclen;
	char	*dup;
	int		i;

	if (!src)
		return (NULL);
	srclen = ft_strlen(src);
	dup = tracked_malloc(shell, sizeof(char) * (srclen + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr_track(t_shell *shell, char const *s, unsigned int start, size_t len)
{
	size_t i;
	char *str;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup_track(shell, ""));
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = tracked_malloc(shell, sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	str[len] = '\0';
	return (str);
}

char	*ft_strjoin_track(t_shell *shell, const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)tracked_malloc(shell, sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}
