/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:49:55 by jpceia            #+#    #+#             */
/*   Updated: 2021/03/24 03:38:35 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

#include <stdlib.h>
#include <unistd.h>

typedef struct s_tape
{
	char *buf;
	size_t start;
} t_tape;

int get_next_line(int fd, char **line);

size_t ft_strlen(const char *str);

char *ft_strcat(char *dest, const char *src);

char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);

char *freeable_empty_string();

#endif
