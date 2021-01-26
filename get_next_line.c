#include "get_next_line.h"

# define malloc(x) NULL

static size_t	len_line(char *str)
{
	size_t 	i; 

	i = 0;
	while (str[i] != '\n')
		i++;
	return (i);
}

static char *complet_line(char **str, char *line)
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

int		get_next_line(int fd, char **line)
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

int main(int ac, char **av)
{
	char *line;
	int fd;
	int gnl;
	int i = 1;
	(void)ac;
	fd = open(av[1], O_RDONLY);
	line = NULL;
	while (1)
		get_next_line(fd, &line);
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
