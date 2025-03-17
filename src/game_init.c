#include "cub3d.h"

void	close_game(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		close_game(game);
		exit(0);
	}
	else if (keycode == KEY_W)
		game->input.key_w = 1;
	else if (keycode == KEY_S)
		game->input.key_s = 1;
	else if (keycode == KEY_A)
		game->input.key_a = 1;
	else if (keycode == KEY_D)
		game->input.key_d = 1;
	else if (keycode == KEY_LEFT)
		game->input.key_left = 1;
	else if (keycode == KEY_RIGHT)
		game->input.key_right = 1;
	else if (keycode == KEY_UP)
		game->input.key_up = 1;
	else if (keycode == KEY_DOWN)
		game->input.key_down = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->input.key_w = 0;
	else if (keycode == KEY_S)
		game->input.key_s = 0;
	else if (keycode == KEY_A)
		game->input.key_a = 0;
	else if (keycode == KEY_D)
		game->input.key_d = 0;
	else if (keycode == KEY_LEFT)
		game->input.key_left = 0;
	else if (keycode == KEY_RIGHT)
		game->input.key_right = 0;
	else if (keycode == KEY_UP)
		game->input.key_up = 0;
	else if (keycode == KEY_DOWN)
		game->input.key_down = 0;
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
	game->input = (t_input){0, 0, 0, 0, 0, 0, 0, 0};
	init_player(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_loop_hook(game->mlx, render_loop, game);
	return (0);
}
