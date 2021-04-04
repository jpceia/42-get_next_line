
#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{

	int fd;
	int index;
	int status;
	char *line;

	status = 1;
	index = 1;
	while (index < argc)
	{
		fd = open(argv[index++], O_RDONLY);
		if (fd < 0)
			continue;
		status = 1;
		while (status > 0)
		{
			status = get_next_line(fd, &line);
			printf("%s\n", line);
			free(line);
		}
		close(fd);
	}
	return (0);
}
