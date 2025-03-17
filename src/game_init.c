#include "cub3d.h"

void	close_game(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		close_game(game);
		exit(0);
	}
	else if (keycode == KEY_W)
		move_forward(game);
	else if (keycode == KEY_S)
		move_backward(game);
	else if (keycode == KEY_A)
		move_left(game);
	else if (keycode == KEY_D)
		move_right(game);
	else if (keycode == KEY_LEFT)
			rotate_right(game);  // Changed from rotate_left
	else if (keycode == KEY_RIGHT)
			rotate_left(game);   // Changed from rotate_right
	return (0);
}

int	close_window(t_game *game)
{
	close_game(game);
	exit(0);
	return (0);
}

int	init_game(t_game *game, t_config *config)
{
	game->config = config;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (1);
	game->win = mlx_new_window(game->mlx, config->width,
			config->height, "Cub3D");
	if (!game->win)
		return (1);
	game->img.img = mlx_new_image(game->mlx, config->width, config->height);
	if (!game->img.img)
		return (1);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		return (1);
		
	// Initialize the player
	init_player(game);
	
	mlx_hook(game->win, 2, 1L << 0, handle_key, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_loop_hook(game->mlx, render_loop, game);
	return (0);
}



// mlx_loop_hook(game->mlx, render, game);