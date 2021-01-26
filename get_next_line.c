/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 08:52:47 by malbrand          #+#    #+#             */
/*   Updated: 2021/01/26 08:55:46 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	len_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	return (i);
}

static char		*complet_line(char **str, char *line)
{
	char	*tmp;

	if ((ft_strchr(*str, '\n')) == NULL)
	{
		line = ft_strdup(*str);
		free(*str);
		*str = NULL;
	}
	else
	{
		line = ft_substr(*str, 0, len_line(*str));
		tmp = *str;
		*str = ft_strdup(*str + len_line(*str) + 1);
		free(tmp);
	}
	return (line);
}

int				get_next_line(int fd, char **line)
{
	static char	*str = NULL;
	int			ret;
	char		*buff;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	while ((!(ft_strchr(str, '\n')) && (ret = read(fd, buff, BUFFER_SIZE))))
	{
		if (ret == -1)
		{
			free(buff);
			buff = NULL;
			return (-1);
		}
		buff[ret] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	*line = complet_line(&str, *line);
	if (str == NULL && ret == 0)
		return (0);
	return (1);
}
