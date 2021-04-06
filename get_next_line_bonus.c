/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:49:24 by jpceia            #+#    #+#             */
/*   Updated: 2021/04/06 18:54:20 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <sys/resource.h>

t_tape	*tape_init(t_tape *p_tape)
{
	if (!p_tape)
		return (NULL);
	if (!p_tape->buf)
	{
		p_tape->buf = malloc(BUFFER_SIZE + 1);
		if (!p_tape->buf)
			return (NULL);
		p_tape->buf[0] = '\0';
		p_tape->start = 0;
	}
	return (p_tape);
}

void	free_tape(t_tape *p_tape)
{
	if (!p_tape)
		return ;
	free(p_tape->buf);
	p_tape->buf = NULL;
}

char	*str_concat_tape(char **line, t_tape *tape, size_t end)
{
	char	*ret;
	char	*sub;

	sub = ft_substr(tape->buf, tape->start, end - tape->start);
	if (!sub)
		return (NULL);
	ret = ft_strjoin(*line, sub);
	free(*line);
	free(sub);
	return (ret);
}

int	gnl_loop(int fd, char **line, t_tape *tape)
{
	size_t	index;
	int		nb;

	index = tape->start;
	while (tape->buf[index] != '\n' && tape->buf[index] != '\0')
		index++;
	*line = str_concat_tape(line, tape, index);
	if (!*line)
		return (GNL_ERR);
	tape->start = index + 1;
	if (tape->buf[index] == '\n')
		return (GNL_NL);
	nb = read(fd, tape->buf, BUFFER_SIZE);
	if (nb < 0)
		return (GNL_ERR);
	if (nb == 0)
		return (GNL_EOF);
	tape->buf[nb] = '\0';
	tape->start = 0;
	return (GNL_CONTINUE);
}

int	get_next_line(int fd, char **line)
{
	static t_tape	tapes[RLIMIT_NOFILE];
	int				status;

	if (fd < 0 || fd >= RLIMIT_NOFILE || BUFFER_SIZE <= 0 || !line)
		return (GNL_ERR);
	*line = freeable_empty_string();
	if (!tape_init(&tapes[fd]) || !*line)
		return (GNL_ERR);
	status = GNL_CONTINUE;
	while (status == GNL_CONTINUE)
		status = gnl_loop(fd, line, &tapes[fd]);
	if (status == GNL_ERR || status == GNL_EOF)
		free_tape(&tapes[fd]);
	return (status);
}
