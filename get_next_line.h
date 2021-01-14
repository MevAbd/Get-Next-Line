/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 18:13:09 by malbrand          #+#    #+#             */
/*   Updated: 2021/01/14 16:55:16 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
# endif

char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(char const *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(char const *s);
char		*ft_strchr(char const *str, int c);
int			get_next_line(int fd, char **line);

#endif
