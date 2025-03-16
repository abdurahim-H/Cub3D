#include "cub3d.h"

void	calculate_ray_direction(t_game *game, int x, t_vector *ray_dir)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)game->config->width - 1.0;
	ray_dir->x = game->player.direction.x + game->player.camera_plane.x * camera_x;
	ray_dir->y = game->player.direction.y + game->player.camera_plane.y * camera_x; 
}

void	perform_dda(t_game *game, t_raycast *ray)
{
	ray->map_x = (int)game->player.position.x;
	ray->map_y = (int)game->player.position.y;
	ray->hit = 0;
}