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
