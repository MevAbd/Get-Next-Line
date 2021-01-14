/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnltest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 16:26:59 by malbrand          #+#    #+#             */
/*   Updated: 2021/01/14 17:45:58 by malbrand         ###   ########.fr       */
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
	(*line) = ft_strjoin(*line, buff);
	free(tmp);
}

int	get_next_line(int fd, char **line)
{
	static char *str;
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	if (fd > -1)
	{
		*line = ft_strdup("");
		if (str)
		{
			(*line) = ft_strdup(str);
			free(str);
		}
		while (((str = ft_strchr(*line, '\n')) == NULL) &&
				(ret = read(fd, buff, BUFFER_SIZE) > 0))
		{
			printf("la\n");
			add_line(line, buff, ret);
		}
		printf("ici\n");
		if(ret == 0 && str == NULL)
			return (0);
		complete_line(line, &str, ret);
		return (ret = -1 ? -1 : 1);
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
	while ((gnl = get_next_line(fd, &line)) == 1)
	{
		printf("%d|%d|%s|\n", gnl, i, line);
		i++;
		free(line);
	}
	printf("%d|%s|\n", gnl, line);
	free(line);
	return (0);
}

