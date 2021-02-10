/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:49:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/02/10 03:09:07 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

int	init_buf(char **buf)
{
	if (*buf == NULL)
	{
		*buf = malloc(BUFFER_SIZE);
		if (!*buf)
			return (-1);
		*buf[0] = 0;
		return (0);
	}
	return (1);
}

int	get_next_line_core(int fd, char **line, int line_idx, int breakline)
{
	static char	*buf = NULL;
	static int	buf_idx = 0;
	int			b;

	b = init_buf(&buf);
	if (b < 0)
		return (-1);
	else if (b > 0)
		while (buf[buf_idx] && buf[buf_idx] != '\n')
			(*line)[line_idx++] = buf[buf_idx++];
	while (buf[buf_idx++] == 0)
	{
		b = read(fd, buf, BUFFER_SIZE - 1);
		if (b <= 0)
			break ;
		buf[b] = 0;
		buf_idx = 0;
		while (buf[buf_idx] && buf[buf_idx] != '\n')
			(*line)[line_idx++] = buf[buf_idx++];
	}
	(*line)[line_idx] = '\0';
	if (buf[buf_idx - 1] != 0)
		return (1);
	free(buf);
	return (b);
}

int	get_next_line(int fd, char **line)
{
	return (get_next_line_core(fd, line, 0, 0));
}
