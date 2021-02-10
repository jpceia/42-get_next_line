/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:49:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/02/10 00:05:00 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

int get_next_line(int fd, char **line)
{
	int		idx;
	int     r;
	char	c;
	
	idx = 0;
	while ((r = read(fd, &c, 1)))
	{
		if (c == '\n')
			break ;
		(*line)[idx] = c;
		idx++;
	}
	(*line)[idx] = '\0';
	return (r);
}

int main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	char *buf;

	buf = malloc(2048);

	while(get_next_line(fd, &buf))
	{
		printf("%s\n", buf);
	}

	close(fd);
}