#include "cub3d.h"

void	calculate_ray_direction(t_game *game, int x, t_vector *ray_dir)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)game->config->width - 1.0;
	ray_dir->x = game->player.direction.x + game->player.camera_plane.x * camera_x;
	ray_dir->y = game->player.direction.y + game->player.camera_plane.y * camera_x; 
}

void init_ray_data(t_game *game, t_raycast *ray)
{
    ray->map_x = (int)game->player.position.x;
    ray->map_y = (int)game->player.position.y;
    ray->hit = 0;
    if (ray->ray_dir.x == 0)
        ray->delta_dist_x = 1e30;
    else
        ray->delta_dist_x = fabs(1.0 / ray->ray_dir.x);
    if (ray->ray_dir.y == 0)
        ray->delta_dist_y = 1e30;
    else
        ray->delta_dist_y = fabs(1.0 / ray->ray_dir.y);
}

void calculate_step_and_side_dist(t_game *game, t_raycast *ray)
{
    if (ray->ray_dir.x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player.position.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.position.x) * ray->delta_dist_x;
    }
    if (ray->ray_dir.y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player.position.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.position.y) * ray->delta_dist_y;
    }
}

void perform_dda_algorithm(t_game *game, t_raycast *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (ray->map_y < 0 || ray->map_x < 0 || 
            ray->map_y >= game->config->map_count || 
            ray->map_x >= (int)strlen(game->config->map[ray->map_y]))
        {
            ray->hit = 1;
            continue;
        }
        
        if (game->config->map[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

// void perform_dda(t_game *game, t_raycast *ray)
// {
//     init_ray_data(game, ray);
//     calculate_step_and_side_dist(game, ray);
//     perform_dda_algorithm(game, ray);
    
//     if (ray->side == 0)
//         ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
//     else
//         ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
// }


void perform_dda(t_game *game, t_raycast *ray)
{
    init_ray_data(game, ray);
    calculate_step_and_side_dist(game, ray);
    perform_dda_algorithm(game, ray);
    
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
        
    // Calculate wall_x - where exactly the ray hit the wall
    if (ray->side == 0) // East or west wall
    {
        // For east/west walls, calculate the exact y-coordinate where the ray hit
        ray->wall_x = game->player.position.y + ray->perp_wall_dist * ray->ray_dir.y;
    }
    else // North or south wall
    {
        // For north/south walls, calculate the exact x-coordinate where the ray hit
        ray->wall_x = game->player.position.x + ray->perp_wall_dist * ray->ray_dir.x;
    }
    
    // Take only the fractional part to normalize between 0 and 1
    ray->wall_x = ray->wall_x - floor(ray->wall_x);
}
