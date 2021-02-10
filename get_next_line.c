/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:49:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/02/10 02:16:06 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{
	static char	*buf = NULL;
	static int	first_call = 1;
	static int	buf_idx = BUFFER_SIZE;;
	int			line_idx;
	int			breakline;
	int			b;

	line_idx = 0;
	breakline = 0;
	if (buf == NULL)
	{
		buf = malloc(BUFFER_SIZE);
		if (!buf)
			return (-1);
	}
	else
	{
		while (buf_idx < BUFFER_SIZE && buf[buf_idx] && buf[buf_idx] != '\n')
			(*line)[line_idx++] = buf[buf_idx++];
		breakline = buf[buf_idx++] == '\n';
	}
	while (!breakline)
	{
		b = read(fd, buf, BUFFER_SIZE - 1);
		buf[b] = 0;
		if (b <= 0)
			break ;
		buf_idx = 0;
		while (buf_idx < BUFFER_SIZE && buf[buf_idx] && buf[buf_idx] != '\n')
			(*line)[line_idx++] = buf[buf_idx++];
		breakline = buf[buf_idx++] == '\n';
	}
	if (breakline)
	{
		(*line)[line_idx] = 0;
		return (1);
	}
	(*line)[line_idx] = 0;
	free(buf);
	return (b);
}
