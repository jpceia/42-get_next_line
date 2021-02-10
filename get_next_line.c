/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:49:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/02/10 01:44:36 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{
	static char	*buf;
	static int	first_call = 1;
	static int	buf_idx = BUFFER_SIZE;;
	int			line_idx;
	int			b;

	line_idx = 0;
	if (first_call)
	{
		buf = malloc(BUFFER_SIZE);
		if (!buf)
			return (-1);
		first_call = 0;
	}
	else
	{
		while (buf_idx < BUFFER_SIZE && buf[buf_idx] && buf[buf_idx] != '\n')
			(*line)[line_idx++] = buf[buf_idx++];
		if (buf[buf_idx++] == '\n')
		{
			(*line)[line_idx] = 0;
			return (1);
		}
	}
	while (1)
	{
		b = read(fd, buf, BUFFER_SIZE - 1);
		buf[b] = 0;
		if (b <= 0)
			break ;
		buf_idx = 0;
		while (buf_idx < BUFFER_SIZE && buf[buf_idx] && buf[buf_idx] != '\n')
			(*line)[line_idx++] = buf[buf_idx++];
		if (buf[buf_idx++] == '\n')
		{
			(*line)[line_idx] = 0;
			return (1);
		}
	}
	(*line)[line_idx] = 0;
	free(buf);
	return (b);
}
