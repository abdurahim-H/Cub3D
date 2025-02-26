#include "cub3d.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	initialize_mlx(t_config config)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, config.width, config.height, "Hello world!");
	img.img = mlx_new_image(mlx, config.width, config.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
		&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

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
	
	// Safety check but should be unnecessary due to process_config's handling
	if (!config.map)
	{
		fprintf(stderr, "Error: No valid map found\n");
		free_config_resources(&config);
		close(fd);
		exit(1);
	}
	
	// Run validation
	if (validate_map(config.map, config.map_count) != 0)
	{
		free_config_resources(&config);
		close(fd);
		exit(1);
	}
	
	print_map(config.map, config.map_count);
	calculate_map_dimensions(config.map, config.map_count);
	close(fd);
	initialize_mlx(config);
	return (0);
}