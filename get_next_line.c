/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:49:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/03/24 03:38:33 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		index = tape.start + 1;
		while (tape.buf[index] != '\n' && tape.buf[index] != '\0')
			index++;
		s1 = *line;
		s2 = ft_substr(tape.buf, tape.start, index - tape.start);
		*line = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
		tape.start = index + 1;
		if (tape.buf[index] == '\n')
			return (1);
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