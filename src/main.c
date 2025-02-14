#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cub3d.h"

int	main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_config	config;

	if (check_arg(argc, argv) != 0)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	init_config(&config);
	line = ft_getline(fd);
	while (line != NULL)
	{
		parse_line(line, &config);
		free(line);
		line = ft_getline(fd);
	}
	close(fd);
	return (0);
}
