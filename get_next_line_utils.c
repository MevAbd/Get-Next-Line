/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 09:09:59 by malbrand          #+#    #+#             */
/*   Updated: 2021/01/27 10:06:22 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*new;
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (i < len && s[start] && start < ft_strlen(s))
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s_cpy;

	i = 0;
	s_cpy = (char *)s;
	if (!s)
		return (NULL);
	while (s_cpy[i])
	{
		if (s_cpy[i] == c)
		{
			return (s_cpy + i);
		}
		i++;
	}
	if (c == '\0')
	{
		return (s_cpy + i);
	}
	return (NULL);
}

char		*ft_strdup(const char *s)
{
	size_t		i;
	char		*s_cpy;

	i = 0;
	if (!s)
		return (NULL);
	s_cpy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s_cpy)
		return (NULL);
	while (s[i])
	{
		s_cpy[i] = s[i];
		i++;
	}
	s_cpy[i] = '\0';
	return (s_cpy);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		s3 = ft_strdup(s1);
		free(s1);
		return (s3);
	}
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[i])
		s3[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[j++] = s2[i++];
	s3[j] = '\0';
	free(s1);
	return (s3);
}
