/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:32:12 by malbrand          #+#    #+#             */
/*   Updated: 2021/01/07 18:34:40 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		j;
	char	*ret;

	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	while (s1[i])
		ret[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ret[j++] = s2[i++];
	ret[j] = '\0';
	return (ret);
}

char	*ft_strdup(char const *s)
{
	size_t	len;
	char	*ret;
	size_t	i;

	len = ft_strlen(s) + 1;
	i = 0;
	if (!(ret = (char *)malloc(sizeof(char) * len)))
		return (NULL);
	while (s[i])
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((size_t)start >= len)
	{
		if (!(ret = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		ret[0] = '\0';
		return (ret);
	}
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char const *str, int c)
{
	char		*ret;
	size_t		i;
	size_t		len;

	i = -1;
	len = ft_strlen(str);
	ret = (char *)str;
	if (c == '\0')
	{
		ret = &ret[len];
		return (ret);
	}
	if (c)
	{
		while (ret[++i])
		{
			if (ret[i] == c)
			{
				ret = &ret[i];
				return (ret);
			}
		}
		return (NULL);
	}
	return (NULL);
}
