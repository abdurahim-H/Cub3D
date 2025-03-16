#include "cub3d.h"
#include <mlx.h>

int	main(int argc, char **argv)
{
	int			fd;
	t_config	config;
	t_game		game;

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
	{
		fprintf(stderr, "Error: No valid map found\n");
		free_config_resources(&config);
		close(fd);
		exit(1);
	}
	if (validate_map(config.map, config.map_count) != 0)
	{
		free_config_resources(&config);
		close(fd);
		exit(1);
	}
	print_map(config.map, config.map_count);
	calculate_map_dimensions(config.map, config.map_count);
	close(fd);
	if (init_game(&game, &config) != 0)
	{
		fprintf(stderr, "Error: Failed to initialize game\n");
		free_config_resources(&config);
		exit(1);
	}
	mlx_loop(game.mlx);
	close_game(&game);
	free_config_resources(&config);
	return (0);
}
