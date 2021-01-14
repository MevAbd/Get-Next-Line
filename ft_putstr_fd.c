/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:25:21 by malbrand          #+#    #+#             */
/*   Updated: 2021/01/14 16:26:38 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s && fd)
		write(fd, s, ft_strlen(s));
}

int main(int ac, char **av)
{
	(void)ac;
	int	fd; 

	fd = open("test.txt", O_RDWR);
	ft_putstr_fd(av[1], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd(av[2], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd(av[3], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd(av[4], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd(av[5], fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd(av[6], fd);
   	return (0);	
}
