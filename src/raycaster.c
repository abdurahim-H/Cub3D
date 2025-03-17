#include "cub3d.h"

t_raycast	compute_ray(t_game *game, int x)
{
	t_raycast	ray;

	calculate_ray_direction(game, x, &ray.ray_dir);
	perform_dda(game, &ray);
	return (ray);
}

void	compute_draw_bounds(t_game *game, double perp_wall_dist,
	t_draw_bounds *bounds)
{
	int	line_height;

	line_height = (int)(game->config->height / perp_wall_dist);
	bounds->start = -line_height / 2 + game->config->height / 2 + game->player.vertical_offset;
	if (bounds->start < 0)
		bounds->start = 0;
	bounds->end = line_height / 2 + game->config->height / 2 + game->player.vertical_offset;
	if (bounds->end >= game->config->height)
		bounds->end = game->config->height - 1;
}

void	draw_line(t_game *game, int x, t_draw_bounds bounds, t_rgb color)
{
	int			y;

	y = bounds.start;
	while (y < bounds.end)
	{
		my_mlx_pixel_put(&game->img, x, y, color);
		y = y + 1;
	}
}

t_rgb	compute_color_ew(t_raycast *ray)
{
	t_rgb		color;

	if (ray->ray_dir.x > 0)
	{
		color.r = 255;
		color.g = 100;
		color.b = 100;
	}
	else
	{
		color.r = 100;
		color.g = 255;
		color.b = 100;
	}
	return (color);
}

t_rgb	compute_color_ns(t_raycast *ray)
{
	t_rgb		color;

	if (ray->ray_dir.y > 0)
	{
		color.r = 100;
		color.g = 100;
		color.b = 255;
	}
	else
	{
		color.r = 255;
		color.g = 255;
		color.b = 100;
	}
	color.r = color.r * 0.7;
	color.g = color.g * 0.7;
	color.b = color.b * 0.7;
	return (color);
}

t_rgb	compute_color(t_raycast *ray)
{
	t_rgb		color;

	if (ray->side == 0)
	{
		color = compute_color_ew(ray);
	}
	else
	{
		color = compute_color_ns(ray);
	}
	return (color);
}

void	process_column(t_game *game, int x)
{
	t_raycast		ray;
	t_draw_bounds	bounds;
	t_rgb			color;

	ray = compute_ray(game, x);
	compute_draw_bounds(game, ray.perp_wall_dist, &bounds);
	color = compute_color(&ray);
	draw_line(game, x, bounds, color);
}

void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->config->width)
	{
		process_column(game, x);
		x = x + 1;
	}
}
