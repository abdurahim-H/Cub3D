#include "cub3d.h"

int load_texture(void *mlx, char *path, t_img *img)
{
    int width;
    int height;
    if (!mlx || !path || !img)
        return (1);
    printf("Attempting to load texture: %s\n", path);
    img->img = mlx_xpm_file_to_image(mlx, path, &width, &height);
    if (!img->img)
    {
        fprintf(stderr, "Error: Failed to load texture: %s\n", path);
        printf("Width: %d, Height: %d\n", width, height);
        return (1);
    }
    
    printf("Successfully loaded texture: %s (%dx%d)\n", path, width, height);
    img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, 
                                  &img->line_length, &img->endian);
    if (!img->addr)
    {
        mlx_destroy_image(mlx, img->img);
        img->img = NULL;
        fprintf(stderr, "Error: Failed to get texture data: %s\n", path);
        return (1);
    }
    printf("Texture data retrieved successfully for: %s\n", path);
    return (0);
}

int	load_textures(t_game *game)
{
	if (!game || !game->config || !game->mlx)
		return (1);
	if (!game->config->tex_no || !game->config->tex_so || 
		!game->config->tex_we || !game->config->tex_ea || 
		!game->config->tex_s)
	{
		fprintf(stderr, "Error: Missing texture path in configuration\n");
		return (1);
	}
	if (load_texture(game->mlx, game->config->tex_no, &game->tex_north))
		return (1);
		
	if (load_texture(game->mlx, game->config->tex_so, &game->tex_south))
	{
		mlx_destroy_image(game->mlx, game->tex_north.img);
		return (1);
	}
		
	if (load_texture(game->mlx, game->config->tex_we, &game->tex_west))
	{
		mlx_destroy_image(game->mlx, game->tex_north.img);
		mlx_destroy_image(game->mlx, game->tex_south.img);
		return (1);
	}
		
	if (load_texture(game->mlx, game->config->tex_ea, &game->tex_east))
	{
		mlx_destroy_image(game->mlx, game->tex_north.img);
		mlx_destroy_image(game->mlx, game->tex_south.img);
		mlx_destroy_image(game->mlx, game->tex_west.img);
		return (1);
	}
		
	if (load_texture(game->mlx, game->config->tex_s, &game->tex_sprite))
	{
		mlx_destroy_image(game->mlx, game->tex_north.img);
		mlx_destroy_image(game->mlx, game->tex_south.img);
		mlx_destroy_image(game->mlx, game->tex_west.img);
		mlx_destroy_image(game->mlx, game->tex_east.img);
		return (1);
	}
	return (0);
}

t_img	*get_wall_texture(t_game *game, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir.x > 0)
			return (&game->tex_west);
		else
			return (&game->tex_east);
	}
	else
	{
		if (ray->ray_dir.y > 0)
			return (&game->tex_north);
		// Otherwise, it hit a south wall
		else
			return (&game->tex_south);
	}
}

t_rgb	get_pixel_color(t_img *img, int x, int y)
{
	t_rgb	color;
	char	*pixel;
	int		offset;

	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	pixel = img->addr + offset;
	if (img->endian == 0) // Little endian
	{
		color.b = pixel[0];
		color.g = pixel[1];
		color.r = pixel[2];
	}
	else
	{
		color.r = pixel[0];
		color.g = pixel[1];
		color.b = pixel[2];
	}
		
	return (color);
}

void	draw_textured_line(t_game *game, int x, t_draw_bounds bounds, t_raycast *ray)
{
	t_img *texture;
	int tex_x, tex_y;
	int y;
	double step, tex_pos;
	int line_height;
	t_rgb color;
		
	texture = get_wall_texture(game, ray);
	tex_x = (int)(ray->wall_x * 64);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= 64)
		tex_x = 63;
	line_height = bounds.end - bounds.start;
	step = 64.0 / (double)line_height;
	tex_pos = 0;
	if (bounds.start < 0)
		tex_pos = step * -bounds.start;
	y = bounds.start;
	while (y < bounds.end)
	{
		if (y >= 0 && y < game->config->height)
		{
			tex_y = (int)tex_pos & 63;
			color = get_pixel_color(texture, tex_x, tex_y);
			if (ray->side == 1)
			{
				color.r = color.r * 0.7;
				color.g = color.g * 0.7;
				color.b = color.b * 0.7;
			}
			my_mlx_pixel_put(&game->img, x, y, color);
		}
		tex_pos += step;
		y++;
	}
}

