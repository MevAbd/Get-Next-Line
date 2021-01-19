/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnltest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:26:59 by malbrand          #+#    #+#             */
/*   Updated: 2021/01/19 09:47:22 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	complete_line(char **line, char **str, int ret)
{
	char	*tmp;

	if (ret == -1)
		return ;
	tmp = *line; 
	*line = ft_substr(*line, 0, *str - *line);
	free(tmp);
	*str = ft_strdup(*str + 1);
}

void	add_line(char **line, char *buff, int ret)
{
	char	*tmp; 

	tmp = *line; 
	buff[ret] = '\0';
	//printf("buff = %s et ret = %d\n", buff, ret);
	(*line) = ft_strjoin(*line, buff);
	free(tmp);
}

int	get_next_line(int fd, char **line)
{
	static char *str;
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	if (fd != 0 && !line)
		return (-1);
	if (fd > -1)
	{
		*line = ft_strdup("");
		if (str)
		{
			(*line) = ft_strdup(str);
			free(str);
		}
		ret = read(fd, buff, BUFFER_SIZE);
		printf("CEST COMMAN = %d\n", ret);
		while ((ret = read(fd, buff, BUFFER_SIZE) > 0) && ((str = ft_strchr(*line, '\n')) == NULL))
		{
			printf("buff = %s line = %s\n, ret = %d\n", buff, *line, ret);
			add_line(line, buff, ret);
		}
		if(ret == 0 && str == NULL)
			return (0);
		complete_line(line, &str, ret);
		return (1);
	}
	else 
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
	if ((gnl = get_next_line(fd, &line)) == 1)
	{
		//printf("%d|%d|%s|\n", gnl, i, line);
		i++;
		free(line);
	}
	//printf("%d|%s|\n", gnl, line);
	free(line);
	return (0);
}

