#include "cub3d.h"

void	move_forward(t_game *game, int diagonal)
{
	double	new_x;
	double	new_y;
	double	speed_multiplier;

	speed_multiplier = 1.0;
	if (diagonal)
		speed_multiplier *= 0.707;
	new_x = game->player.position.x + game->player.direction.x
		* game->player.move_speed * speed_multiplier;
	new_y = game->player.position.y + game->player.direction.y
		* game->player.move_speed * speed_multiplier;
	if (new_y < 0 || new_y >= game->config->map_count)
		return ;
	if (new_x < 0 || new_x >= ft_strlen(game->config->map[(int)new_y]))
		return ;
	if (game->config->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}

void	move_backward(t_game *game, int diagonal)
{
	double	new_x;
	double	new_y;
	double	speed_multiplier;

	speed_multiplier = 1.0;
	if (diagonal)
		speed_multiplier *= 0.707;
	new_x = game->player.position.x - game->player.direction.x
		* game->player.move_speed * speed_multiplier;
	new_y = game->player.position.y - game->player.direction.y
		* game->player.move_speed * speed_multiplier;
	if (new_y < 0 || new_y >= game->config->map_count)
		return ;
	if (new_x < 0 || new_x >= ft_strlen(game->config->map[(int)new_y]))
		return ;
	if (game->config->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}

void	move_left(t_game *game, int diagonal)
{
	double	new_x;
	double	new_y;
	double	speed_multiplier;

	speed_multiplier = 1.0;
	if (diagonal)
		speed_multiplier *= 0.707;
		
	new_x = game->player.position.x - game->player.direction.y
		* game->player.move_speed * speed_multiplier;
	new_y = game->player.position.y + game->player.direction.x
		* game->player.move_speed * speed_multiplier;
	if (new_y < 0 || new_y >= game->config->map_count)
		return ;
	if (new_x < 0 || new_x >= ft_strlen(game->config->map[(int)new_y]))
		return ;
	if (game->config->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}

void	move_right(t_game *game, int diagonal)
{
	double	new_x;
	double	new_y;
	double	speed_multiplier;

	speed_multiplier = 1.0;
	if (diagonal)
		speed_multiplier *= 0.707;
	new_x = game->player.position.x + game->player.direction.y
		* game->player.move_speed * speed_multiplier;
	new_y = game->player.position.y - game->player.direction.x
		* game->player.move_speed * speed_multiplier;
	if (new_y < 0 || new_y >= game->config->map_count)
		return ;
	if (new_x < 0 || new_x >= ft_strlen(game->config->map[(int)new_y]))
		return ;
	if (game->config->map[(int)new_y][(int)new_x] != '1')
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}

void	rotate_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = game->player.direction.x;
	old_plane_x = game->player.camera_plane.x;
	cos_rot = cos(-game->player.rot_speed);
	sin_rot = sin(-game->player.rot_speed);
	game->player.direction.x = game->player.direction.x * cos_rot
		- game->player.direction.y * sin_rot;
	game->player.direction.y = old_dir_x * sin_rot
		+ game->player.direction.y * cos_rot;
	game->player.camera_plane.x = game->player.camera_plane.x
		* cos_rot - game->player.camera_plane.y * sin_rot;
	game->player.camera_plane.y = old_plane_x * sin_rot
		+ game->player.camera_plane.y * cos_rot;
}

void	rotate_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_rot;
	double	sin_rot;

	old_dir_x = game->player.direction.x;
	old_plane_x = game->player.camera_plane.x;
	cos_rot = cos(game->player.rot_speed);
	sin_rot = sin(game->player.rot_speed);
	game->player.direction.x = game->player.direction.x * cos_rot
		- game->player.direction.y * sin_rot;
	game->player.direction.y = old_dir_x * sin_rot
		+ game->player.direction.y * cos_rot;
	game->player.camera_plane.x = game->player.camera_plane.x
		* cos_rot - game->player.camera_plane.y * sin_rot;
	game->player.camera_plane.y = old_plane_x * sin_rot
		+ game->player.camera_plane.y * cos_rot;
}

void	look_up(t_game *game)
{
	if (game->player.vertical_offset > -game->player.vertical_limit)
		game->player.vertical_offset -= 15.0;
}

void	look_down(t_game *game)
{
	if (game->player.vertical_offset < game->player.vertical_limit)
		game->player.vertical_offset += 15.0;
}
