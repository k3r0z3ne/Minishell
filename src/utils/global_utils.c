/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: witong <witong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:14:49 by witong            #+#    #+#             */
/*   Updated: 2025/01/07 16:35:38 by witong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isupper(int c)
{
	if (c > 64 && c < 91)
		return (1);
	return (0);
}

int	count_line(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**arraydup(char **array)
{
	char	**dup;
	int		lc;

	lc = count_line(array);
	dup = (char **)malloc(sizeof(char *) * (lc + 1));
	if (!dup)
		return (NULL);
	dup[lc] = NULL;
	lc = 0;
	while (array[lc])
	{
		dup[lc] = ft_strdup(array[lc]);
		if (!dup[lc])
		{
			free_array(dup);
			return (NULL);
		}
		lc++;
	}
	return (dup);
}

char	*ft_strdup_track(t_shell *shell, char *src)
{
	int		srclen;
	char	*dup;
	int		i;

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
	return (dup);
}

char	*ft_substr_track(t_shell *shell, char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup_track(shell, ""));
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = tracked_malloc(shell, sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	else if (s == 0)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = s[start++];
	return (str);
}
