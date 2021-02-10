/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <jpceia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 01:38:59 by jpceia            #+#    #+#             */
/*   Updated: 2021/02/10 01:40:14 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	char *str;

	str = malloc(2048);

	while(get_next_line(fd, &str))
	{
		printf("%s\n", str);
	}

	close(fd);
}