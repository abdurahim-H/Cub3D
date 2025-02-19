#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cub3d.h"

// int	main(int argc, char **argv)
// {
// 	int			fd;
// 	t_config	config;

// 	fd = 0;
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
// 	if (!config.map)
// 		config.map = collect_map_lines_rest(fd, &config.map_count, config.map);
// 	print_map(config.map, config.map_count);
// 	calculate_map_dimensions(config.map, config.map_count);
// 	close(fd);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	int			fd;
	t_config	config;

	fd = 0;
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
		config.map = collect_map_lines_rest(fd, &config.map_count, config.map);
	if (validate_map(config.map, config.map_count) != 0)
		exit(1);
	print_map(config.map, config.map_count);
	calculate_map_dimensions(config.map, config.map_count);
	close(fd);
	return (0);
}
