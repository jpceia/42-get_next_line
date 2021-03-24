/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:49:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/03/24 04:05:16 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_tape *tape_init(t_tape *p_tape)
{
	if (!p_tape)
		return (NULL);
	if (!p_tape->buf)
	{
		p_tape->buf = malloc(BUFFER_SIZE + 1);
		if (!p_tape->buf)
			return (NULL);
		p_tape->buf[0] = '\0';
		p_tape->start = BUFFER_SIZE;
	}
	return (p_tape);
}

char *str_concat_tape(char **line, t_tape *tape, size_t end)
{
	char *ret;
	char *sub;

	sub = ft_substr(tape->buf, tape->start, end - tape->start);
	ret = ft_strjoin(*line, sub);
	free(*line);
	free(sub);
	return (ret);
}

int get_next_line(int fd, char **line)
{
	static t_tape tapes[1024];
	t_tape *tape;
	size_t index;
	int nb;

	tape = &tapes[fd];
	if (!tape_init(tape) || !(*line = freeable_empty_string()))
		return (-1);
	while (1)
	{
		index = tape->start + 1;
		while (tape->buf[index] != '\n' && tape->buf[index] != '\0' && index <= BUFFER_SIZE)
			index++;
		*line = str_concat_tape(line, tape, index);
		tape->start = index + 1;
		if (tape->buf[index] == '\n')
			return (1);
		if ((nb = read(fd, tape->buf, BUFFER_SIZE)) <= 0)
			return (nb);
		tape->buf[nb] = '\0';
		tape->start = 0;
	}
	return (-1);
}