#include "cub3d.h"

static void draw_sprite_stripe(t_game *game, int stripe, int sprite_screen_x, 
                               int sprite_height, t_vector transform)
{
    int tex_x;
    int y;
    int d;
    int tex_y;
    t_rgb color;
    int sprite_width;
    
    sprite_width = sprite_height;
    
    tex_x = (256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * 64 / sprite_width) / 256;
    
    if (stripe >= 0 && stripe < game->config->width && transform.y > 0)
    {
        if (transform.y < game->zbuffer[stripe])
        {
            y = -sprite_height / 2 + game->config->height / 2;
            if (y < 0) y = 0;
            
            while (y < sprite_height / 2 + game->config->height / 2)
            {
                if (y < game->config->height)
                {
                    d = y * 256 - game->config->height * 128 + sprite_height * 128;
                    tex_y = ((d * 64) / sprite_height) / 256;
                    
                    color = get_pixel_color(&game->tex_sprite, tex_x, tex_y);
                    
                    if (!(color.r == 0 && color.g == 0 && color.b == 0))
                    {
                        my_mlx_pixel_put(&game->img, stripe, y, color);
                    }
                }
                y++;
            }
        }
    }
}

static void render_sprite(t_game *game, t_sprite *sprite)
{
    t_vector sprite_pos;
    t_vector transform;
    int sprite_screen_x;
    int sprite_height;
    int draw_start_x, draw_end_x;
    int stripe;
    
    sprite_pos.x = sprite->x - game->player.position.x;
    sprite_pos.y = sprite->y - game->player.position.y;
    
    double inv_det = 1.0 / (game->player.camera_plane.x * game->player.direction.y - 
                          game->player.direction.x * game->player.camera_plane.y);
    
    transform.x = inv_det * (game->player.direction.y * sprite_pos.x - 
                           game->player.direction.x * sprite_pos.y);
    transform.y = inv_det * (-game->player.camera_plane.y * sprite_pos.x + 
                           game->player.camera_plane.x * sprite_pos.y);
    
    sprite_screen_x = (int)((game->config->width / 2) * (1 + transform.x / transform.y));
    
    sprite_height = abs((int)(game->config->height / transform.y));
    
    draw_start_x = -sprite_height / 2 + sprite_screen_x;
    if (draw_start_x < 0) draw_start_x = 0;
    
    draw_end_x = sprite_height / 2 + sprite_screen_x;
    if (draw_end_x >= game->config->width) draw_end_x = game->config->width - 1;
    
    stripe = draw_start_x;
    while (stripe < draw_end_x)
    {
        draw_sprite_stripe(game, stripe, sprite_screen_x, sprite_height, transform);
        stripe++;
    }
}

void update_zbuffer(t_game *game, int x, double distance)
{
    if (game->zbuffer)
    {
        game->zbuffer[x] = distance;
    }
}

void render_sprites(t_game *game)
{
    int i;
    
    if (!game->sprites || game->num_sprites <= 0)
        return;
    
    calculate_sprite_distances(game);
    
    sort_sprites(game);
    
    i = 0;
    while (i < game->num_sprites)
    {
        render_sprite(game, &game->sprites[i]);
        i++;
    }
}
