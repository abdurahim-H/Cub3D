#include "cub3d.h"


void draw_transparent_rectangle(t_game *game, int x, int y, int width,
		int height, t_rgb color, int alpha)
{
    int i, j;
    t_rgb existing_color;
    t_rgb blended_color;
    
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            // Skip pixels outside the screen
            if (x + j < 0 || y + i < 0 || 
                x + j >= game->config->width || 
                y + i >= game->config->height)
                continue;
            
            // Get existing pixel color - we need to blend with it
            char *pixel = game->img.addr + 
                         ((y + i) * game->img.line_length + 
                         (x + j) * (game->img.bits_per_pixel / 8));
            
            // Extract RGB from pixel
            if (game->img.endian == 0) // Little endian
            {
                existing_color.b = pixel[0];
                existing_color.g = pixel[1];
                existing_color.r = pixel[2];
            }
            else // Big endian
            {
                existing_color.r = pixel[0];
                existing_color.g = pixel[1];
                existing_color.b = pixel[2];
            }
            
            // Blend colors based on alpha
            blended_color.r = (color.r * alpha + existing_color.r * (255 - alpha)) / 255;
            blended_color.g = (color.g * alpha + existing_color.g * (255 - alpha)) / 255;
            blended_color.b = (color.b * alpha + existing_color.b * (255 - alpha)) / 255;
            
            // Put blended pixel back
            my_mlx_pixel_put(&game->img, x + j, y + i, blended_color);
        }
    }
}

