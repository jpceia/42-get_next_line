/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 01:38:59 by jpceia            #+#    #+#             */
/*   Updated: 2021/03/24 03:28:17 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	(void)argc;

	int fd = open(argv[1], O_RDONLY);
	char *str;
	int e;

	e = 1;
	while (e)
	{
		e = get_next_line(fd, &str);
		printf("%s\n", str);
		if (e <= 0)
			break;
	}

	close(fd);
}