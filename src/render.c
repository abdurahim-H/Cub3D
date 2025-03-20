#include "cub3d.h"

void	draw_section(t_game *game, int y_start, int y_end, t_rgb color)
{
	int		x;
	int		y;

	y = y_start;
	while (y < y_end)
	{
		x = 0;
		while (x < game->config->width)
		{
			my_mlx_pixel_put(&game->img, x, y, color);
			x = x + 1;
		}
		y = y + 1;
	}
}

// void render(void *param)
// {
//     t_game      *game;
//     t_rgb       floor_color;
//     t_rgb       ceiling_color;
//     int         horizon_line;

//     game = (t_game *)param;
//     floor_color.r = game->config->floor_r;
//     floor_color.g = game->config->floor_g;
//     floor_color.b = game->config->floor_b;
//     ceiling_color.r = game->config->ceiling_r;
//     ceiling_color.g = game->config->ceiling_g;
//     ceiling_color.b = game->config->ceiling_b;
//     horizon_line = game->config->height / 2 + game->player.vertical_offset;
//     if (horizon_line < 0)
//         horizon_line = 0;
//     if (horizon_line > game->config->height)
//         horizon_line = game->config->height;
//     draw_section(game, 0, horizon_line, ceiling_color);
//     draw_section(game, horizon_line, game->config->height, floor_color);
//     cast_rays(game);
    
//     // Render sprites after walls
//     render_sprites(game);
    
//     // Only put image to window if we have a window (not in save mode)
//     if (game->win)
//         mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
// }

void render(void *param)
{
    t_game      *game;
    t_rgb       floor_color;
    t_rgb       ceiling_color;
    int         horizon_line;

    game = (t_game *)param;
    floor_color.r = game->config->floor_r;
    floor_color.g = game->config->floor_g;
    floor_color.b = game->config->floor_b;
    ceiling_color.r = game->config->ceiling_r;
    ceiling_color.g = game->config->ceiling_g;
    ceiling_color.b = game->config->ceiling_b;
    horizon_line = game->config->height / 2 + game->player.vertical_offset;
    if (horizon_line < 0)
        horizon_line = 0;
    if (horizon_line > game->config->height)
        horizon_line = game->config->height;
    draw_section(game, 0, horizon_line, ceiling_color);
    draw_section(game, horizon_line, game->config->height, floor_color);
    cast_rays(game);
    render_sprites(game);
    draw_minimap(game);
    if (game->win)
        mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}


void	process_input(t_game *game)
{
	int	diagonal;

	diagonal = (game->input.key_w || game->input.key_s) && 
			  (game->input.key_a || game->input.key_d);
	if (game->input.key_w)
		move_forward(game, diagonal);
	if (game->input.key_s)
		move_backward(game, diagonal);
	if (game->input.key_a)
		move_left(game, diagonal);
	if (game->input.key_d)
		move_right(game, diagonal);
	if (game->input.key_left)
		rotate_right(game);
	if (game->input.key_right)
		rotate_left(game);
	// if (game->input.key_up)
	// 	look_down(game);
	// if (game->input.key_down)
	// 	look_up(game);
}

int	render_loop(void *param)
{
	t_game *game;

	game = (t_game *)param;
	process_input(game);
	render(game);
	return (0);
}
