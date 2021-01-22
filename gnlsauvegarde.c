/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GNLGNL.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 09:47:34 by malbrand          #+#    #+#             */
/*   Updated: 2021/01/21 13:16:04 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	complet_line(char **line, char *buff, char **str, int ret)
{
	char	*tmp;

	if (ret == -1)
		return ;
	tmp = (*line);
	buff = ft_substr(buff, 0, ft_strlen(buff) - ft_strlen(*str));
	(*line) = ft_strjoin(*line, buff);
	free(tmp);
	*str = ft_strdup((*str) + 1);
}

void	add_line(char **line, char *buff, int ret)
{
	char	*tmp;

	tmp = (*line);
	buff[ret] = '\0';
	(*line) = ft_strjoin(*line, buff);
	free(tmp);
}

int		get_next_line(int fd, char **line)
{
	static char	*str;
	char 		buff[BUFFER_SIZE + 1];
	int			ret;

	if (fd != 0 && !line)
		return (-1);
	if (fd > -1)
	{
		(*line) = ft_strdup("");
		if (str)
		{
			if (str[0] == '\n')
			{
				(*line) = ft_strdup("");
				str = ft_strdup(str + 1);
				return (1);
			}
			(*line) = ft_strdup(str);
			free(str);
		}
		while ((ret = read(fd, buff, BUFFER_SIZE)) > 0 && (str = ft_strchr(buff, '\n')) == NULL)
			add_line(line, buff, ret);
		if (ret == 0)
			return (0);
		complet_line(line, buff, &str, ret);
		return ((ret == -1) ? -1 : 1);
	}
	return (-1);
}

int main(int ac, char **av)
{
	char *line;
	int fd;
	int gnl;
	int i = 1;
	(void)ac;
	fd = open(av[1], O_RDONLY);
	line = NULL;
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		printf("%d|%d|LINEEEEEEEEEEEEE	%s|\n", gnl, i, line);
		i++;
		free(line);
		line = NULL;
	}
	printf("%d|%s|\n", gnl, line);
	free(line);
	return (0);
}
