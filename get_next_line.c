/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:49:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/03/24 03:26:59 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

size_t ft_strlen(const char *str)
{
	size_t index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

static char *ft_strcat(char *dest, const char *src)
{
	int n;
	int index;

	n = ft_strlen(dest);
	index = 0;
	while (src[index])
	{
		dest[n + index] = src[index];
		index++;
	}
	dest[n + index] = 0;
	return (dest);
}

char *ft_strjoin(char const *s1, char const *s2)
{
	int size;
	char *res;

	size = ft_strlen(s1);
	size += ft_strlen(s2);
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	ft_strcat(res, s1);
	ft_strcat(res, s2);
	return (res);
}

char *ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t index;
	size_t s_len;
	char *res;

	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (start + len > s_len)
		len = s_len - start;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	index = 0;
	while (s[start + index] && index < len)
	{
		res[index] = s[start + index];
		index++;
	}
	res[index] = '\0';
	return (res);
}

typedef struct s_tape
{
	char *buf;
	size_t start;
} t_tape;

char *freeable_empty_string()
{
	char *e;

	if (!(e = malloc(1)))
		return (NULL);
	*e = '\0';
	return (e);
}

int get_next_line(int fd, char **line)
{
	char *s1;
	char *s2;
	static t_tape tape;
	size_t index;
	int nb;

	if (!tape.buf)
	{
		tape.buf = malloc(BUFFER_SIZE + 1);
		tape.buf[0] = '\0';
		if (!tape.buf)
			return (-1);
		tape.start = BUFFER_SIZE;
	}

	*line = freeable_empty_string();
	if (!*line)
		return (-1);

	while (1)
	{
		// get the next nl
		index = tape.start + 1;
		while (index <= BUFFER_SIZE)
		{
			if (tape.buf[index] == '\n' || index == BUFFER_SIZE)
			{
				s1 = *line;
				s2 = ft_substr(tape.buf, tape.start, index - tape.start);
				*line = ft_strjoin(s1, s2);
				free(s1);
				free(s2);
				tape.start = index + 1;
				if (index == BUFFER_SIZE)
					break;
				return (1);
			}
			index++;
		}
		nb = read(fd, tape.buf, BUFFER_SIZE);
		if (nb < 0)
			return (-1);
		if (nb == 0)
			return (0);
		tape.buf[nb] = '\0';
		tape.start = 0;
	}
	return (-1);
}