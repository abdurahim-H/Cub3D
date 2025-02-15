#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cub3d.h"

// int	main(int argc, char **argv)
// {
// 	int			fd;
// 	t_config	config;
// 	int			map_count;
// 	char		**map;

// 	fd = 0;
// 	map_count = 0;
// 	map = NULL;
// 	if (check_arg(argc, argv) != 0)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	init_config(&config);
// 	process_config(fd, &config);
// 	map = collect_map_lines_rest(fd, &map_count);
// 	config.map = map;
// 	print_map(config.map, map_count);
// 	calculate_map_dimensions(map, map_count);
// 	close(fd);
// 	return (0);
// }


int	main(int argc, char **argv)
{
	int			fd;
	t_config	config;
	int			map_count;

	fd = 0;
	map_count = 0;
	if (check_arg(argc, argv) != 0)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	init_config(&config);
	process_config(fd, &config);
	if (!config.map)
		config.map = collect_map_lines_rest(fd, &map_count);
	else
		map_count = 0;
	print_map(config.map, map_count);
	calculate_map_dimensions(config.map, map_count);
	close(fd);
	return (0);
}
