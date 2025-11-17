/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 08:52:47 by malbrand          #+#    #+#             */
/*   Updated: 2021/01/27 10:15:19 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	len_line(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static char		*complet_line(char **str)
{
	char	*line;
	char	*tmp;
	char	*new_str;

	if (!str || !*str)
		return (NULL);
	if ((ft_strchr(*str, '\n')) == NULL)
	{
		line = ft_strdup(*str);
		free(*str);
		*str = NULL;
	}
	else
	{
		line = ft_substr(*str, 0, len_line(*str) + 1);
		tmp = *str;
		new_str = ft_strdup(*str + len_line(*str) + 1);
		free(tmp);
		*str = new_str;
	}
	return (line);
}

char			*get_next_line(int fd)
{
	static char	*str = NULL;
	int			ret;
	char		*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	ret = 1;
	while (ret > 0 && (!str || !ft_strchr(str, '\n')))
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buff);
			if (str)
				free(str);
			str = NULL;
			return (NULL);
		}
		buff[ret] = '\0';
		str = ft_strjoin(str, buff);
		if (!str)
		{
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	if (ret == 0 && (!str || str[0] == '\0'))
	{
		if (str)
		{
			free(str);
			str = NULL;
		}
		return (NULL);
	}
	line = complet_line(&str);
	if (!line && str == NULL)
		return (NULL);
	return (line);
}
