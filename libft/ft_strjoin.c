/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenon <xenon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 12:23:57 by arotondo          #+#    #+#             */
/*   Updated: 2025/02/12 01:13:52 by xenon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	srclen;
	size_t	i;
	char	*ret;

	srclen = ft_strlen(s1);
	i = 0;
	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	ret = (char *)ft_calloc((srclen + ft_strlen(s2) + 1), sizeof(char));
	if (!ret)
		return (free (s1), NULL);
	while (s1[i] != '\0')
	{
		ret[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ret[srclen + i] = s2[i];
		i++;
	}
	return (free (s1), ret);
}


char	*ft_strjoin2(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = '\0';
		return (str);
	}
	return (NULL);
}