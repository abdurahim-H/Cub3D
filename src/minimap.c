#include "cub3d.h"

// void draw_minimap_square(t_game *game, int x, int y, t_rgb color)
// {
//     int map_x;
//     int map_y;
//     int size;
//     int i, j;
    
//     // Minimap settings
//     size = 8;  // Size of each tile in pixels
//     map_x = 20; // Padding from left edge of screen
//     map_y = 20; // Padding from top edge of screen
    
//     // Draw filled square
//     for (i = 0; i < size; i++)
//     {
//         for (j = 0; j < size; j++)
//         {
//             my_mlx_pixel_put(&game->img, map_x + x * size + i,
// 					map_y + y * size + j, color);
//         }
//     }
// }

void draw_simple_square(t_game *game, int x, int y, int width, int height, t_rgb color)
{
    int i, j;
    
    // Ensure we don't draw outside the screen
    if (x < 0 || y < 0 || x + width >= game->config->width || y + height >= game->config->height)
        return;
    
    // Draw a filled rectangle
    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            my_mlx_pixel_put(&game->img, x + i, y + j, color);
        }
    }
}


void draw_minimap_square(t_game *game, int x, int y, t_rgb color, int tile_size)
{
    int map_x;
    int map_y;
    int i, j;
    int padding = 10; // Padding around the minimap content
    
    // Calculate minimap position
    map_x = 20 + padding; // X position with padding
    map_y = 20 + padding; // Y position with padding
    
    // Draw filled square
    for (i = 0; i < tile_size; i++)
    {
        for (j = 0; j < tile_size; j++)
        {
            my_mlx_pixel_put(&game->img, map_x + x * tile_size + i, map_y + y * tile_size + j, color);
        }
    }
}

// void draw_player_direction(t_game *game, t_rgb color)
// {
//     double dir_x, dir_y;
//     double line_length;
//     int map_x, map_y;
//     int size;
//     int i;
//     double step_x, step_y;
//     int player_map_x, player_map_y;
//     int end_x, end_y;
    
//     // Minimap settings
//     size = 8;
//     map_x = 20;
//     map_y = 20;
//     line_length = 5.0; // Length of direction line (in tiles)
    
//     // Calculate player position on minimap
//     player_map_x = map_x + (int)(game->player.position.x * size) + size / 2;
//     player_map_y = map_y + (int)(game->player.position.y * size) + size / 2;
    
//     // Calculate end point of direction line
//     dir_x = game->player.direction.x * line_length * size;
//     dir_y = game->player.direction.y * line_length * size;
//     end_x = player_map_x + (int)dir_x;
//     end_y = player_map_y + (int)dir_y;
    
//     // Calculate steps for drawing line
//     int steps = (int)(sqrt(dir_x * dir_x + dir_y * dir_y));
//     if (steps == 0) steps = 1;
//     step_x = dir_x / steps;
//     step_y = dir_y / steps;
    
//     // Draw line representing player direction
//     for (i = 0; i < steps; i++)
//     {
//         int x = player_map_x + (int)(step_x * i);
//         int y = player_map_y + (int)(step_y * i);
        
//         my_mlx_pixel_put(&game->img, x, y, color);
//     }
// }

void draw_player_direction(t_game *game, t_rgb color, int tile_size)
{
    double dir_x, dir_y;
    double line_length;
    int map_x, map_y;
    int player_map_x, player_map_y;
    int end_x, end_y;
    int i;
    double step_x, step_y;
    int padding = 10; // Padding around the minimap content
    
    // Calculate minimap position
    map_x = 20 + padding;
    map_y = 20 + padding;
    line_length = 3.0; // Shorter line for better visibility
    
    // Calculate player position on minimap
    player_map_x = map_x + (int)(game->player.position.x * tile_size) + tile_size / 2;
    player_map_y = map_y + (int)(game->player.position.y * tile_size) + tile_size / 2;
    
    // Calculate end point of direction line
    dir_x = game->player.direction.x * line_length * tile_size;
    dir_y = game->player.direction.y * line_length * tile_size;
    end_x = player_map_x + (int)dir_x;
    end_y = player_map_y + (int)dir_y;
    
    // Calculate steps for drawing line
    int steps = (int)(sqrt(dir_x * dir_x + dir_y * dir_y));
    if (steps == 0) steps = 1;
    step_x = dir_x / steps;
    step_y = dir_y / steps;
    
    // Draw line representing player direction
    for (i = 0; i < steps; i++)
    {
        int x = player_map_x + (int)(step_x * i);
        int y = player_map_y + (int)(step_y * i);
        
        my_mlx_pixel_put(&game->img, x, y, color);
    }
}

// void draw_minimap_border(t_game *game)
// {
//     int map_width;
//     int map_height;
//     int size;
//     int map_x, map_y;
//     t_rgb border_color;
//     int i;
//     int max_row_length = 0;
    
//     // Minimap settings
//     size = 8;
//     map_x = 15;
//     map_y = 15;
    
//     // Find the width of the longest map row
//     for (i = 0; i < game->config->map_count; i++)
//     {
//         int row_length = strlen(game->config->map[i]);
//         if (row_length > max_row_length)
//             max_row_length = row_length;
//     }
    
//     // Calculate map dimensions in pixels
//     map_width = max_row_length * size + 10;  // Width based on longest row
//     map_height = game->config->map_count * size + 10;  // Height based on number of rows
    
//     // Border color
//     border_color.r = 255;
//     border_color.g = 255;
//     border_color.b = 255;
    
//     // Draw horizontal borders
//     for (i = 0; i < map_width; i++)
//     {
//         my_mlx_pixel_put(&game->img, map_x + i, map_y, border_color);
//         my_mlx_pixel_put(&game->img, map_x + i, map_y + map_height, border_color);
//     }
    
//     // Draw vertical borders
//     for (i = 0; i < map_height; i++)
//     {
//         my_mlx_pixel_put(&game->img, map_x, map_y + i, border_color);
//         my_mlx_pixel_put(&game->img, map_x + map_width, map_y + i, border_color);
//     }
// }


// void draw_sprites_on_minimap(t_game *game)
// {
//     int i;
//     t_rgb sprite_color;
    
//     // Sprite color (yellow)
//     sprite_color.r = 255;
//     sprite_color.g = 255;
//     sprite_color.b = 0;
    
//     // Draw each sprite
//     for (i = 0; i < game->num_sprites; i++)
//     {
//         int sprite_map_x = (int)game->sprites[i].x;
//         int sprite_map_y = (int)game->sprites[i].y;
        
//         draw_minimap_square(game, sprite_map_x, sprite_map_y, sprite_color);
//     }
// }

// void draw_sprites_on_minimap(t_game *game)
// {
//     int i;
//     t_rgb sprite_color;
    
//     // Sprite color (yellow)
//     sprite_color.r = 255;
//     sprite_color.g = 255;
//     sprite_color.b = 0;
    
//     // Draw each sprite
//     for (i = 0; i < game->num_sprites; i++)
//     {
//         // Validate sprite coordinates
//         if (game->sprites[i].x < 0 || game->sprites[i].y < 0 ||
//             game->sprites[i].x >= game->config->map_count ||
//             game->sprites[i].y >= (int)strlen(game->config->map[(int)game->sprites[i].x]))
//         {
//             continue;  // Skip invalid sprites
//         }
        
//         int sprite_map_x = (int)game->sprites[i].x;
//         int sprite_map_y = (int)game->sprites[i].y;
        
//         draw_minimap_square(game, sprite_map_x, sprite_map_y, sprite_color);
//     }
// }

void draw_sprites_on_minimap(t_game *game, int tile_size)
{
    int i;
    t_rgb sprite_color;
    
    // Sprite color (bright cyan - more visible)
    sprite_color.r = 0;
    sprite_color.g = 255;
    sprite_color.b = 255;
    
    // Draw each sprite
    for (i = 0; i < game->num_sprites; i++)
    {
        // Validate sprite coordinates
        if (game->sprites[i].x < 0 || game->sprites[i].y < 0 ||
            game->sprites[i].y >= game->config->map_count ||
            (int)game->sprites[i].x >= (int)strlen(game->config->map[(int)game->sprites[i].y]))
        {
            continue;  // Skip invalid sprites
        }
        
        int sprite_map_x = (int)game->sprites[i].x;
        int sprite_map_y = (int)game->sprites[i].y;
        
        draw_minimap_square(game, sprite_map_x, sprite_map_y, sprite_color, tile_size);
    }
}

t_vector draw_minimap_background(t_game *game, int tile_size)
{
    int max_row_length = 0;
    int i;
    int padding = 10; // Padding around the minimap content
    t_rgb bg_color;
    t_vector size;
    
    // Find the width of the longest map row
    for (i = 0; i < game->config->map_count; i++)
    {
        int row_length = strlen(game->config->map[i]);
        if (row_length > max_row_length)
            max_row_length = row_length;
    }
    
    // Calculate map dimensions in pixels
    size.x = max_row_length * tile_size + padding * 2;
    size.y = game->config->map_count * tile_size + padding * 2;
    
    // Background color (dark blue, semi-transparent)
    bg_color.r = 10;
    bg_color.g = 20;
    bg_color.b = 40;
    
    // Draw semi-transparent background
    draw_transparent_rectangle(game, 20, 20, size.x, size.y, bg_color, 180);
    
    return size;
}

void draw_minimap_border(t_game *game, t_vector size)
{
    t_rgb border_color;
    int i, j;
    int thickness = 2; // Border thickness
    
    // Border color (bright blue)
    border_color.r = 50;
    border_color.g = 120;
    border_color.b = 255;
    
    // Draw horizontal borders with thickness
    for (i = 0; i < thickness; i++)
    {
        for (j = 0; j < size.x; j++)
        {
            my_mlx_pixel_put(&game->img, 20 + j, 20 + i, border_color);
            my_mlx_pixel_put(&game->img, 20 + j, 20 + size.y - 1 - i, border_color);
        }
    }
    
    // Draw vertical borders with thickness
    for (i = 0; i < thickness; i++)
    {
        for (j = 0; j < size.y; j++)
        {
            my_mlx_pixel_put(&game->img, 20 + i, 20 + j, border_color);
            my_mlx_pixel_put(&game->img, 20 + size.x - 1 - i, 20 + j, border_color);
        }
    }
}


// void draw_minimap(t_game *game)
// {
//     int x, y;
//     t_rgb wall_color;
//     t_rgb floor_color;
//     t_rgb player_color;
    
//     // Define colors
//     wall_color.r = 128;
//     wall_color.g = 128;
//     wall_color.b = 128;
    
//     floor_color.r = 0;
//     floor_color.g = 0;
//     floor_color.b = 0;
    
//     player_color.r = 255;
//     player_color.g = 0;
//     player_color.b = 0;
    
//     // Draw map tiles
//     for (y = 0; y < game->config->map_count; y++)
//     {
//         for (x = 0; x < (int)strlen(game->config->map[y]); x++)
//         {
//             if (game->config->map[y][x] == '1')
//                 draw_minimap_square(game, x, y, wall_color);
//             else if (game->config->map[y][x] == '0' || 
//                     game->config->map[y][x] == 'N' || 
//                     game->config->map[y][x] == 'S' || 
//                     game->config->map[y][x] == 'E' || 
//                     game->config->map[y][x] == 'W')
//                 draw_minimap_square(game, x, y, floor_color);
//         }
//     }
    
//     // Draw sprites
//     draw_sprites_on_minimap(game);
    
//     // Draw player position
//     draw_minimap_square(game, (int)game->player.position.x, 
//                        (int)game->player.position.y, player_color);
    
//     // Draw player direction
//     draw_player_direction(game, player_color);
    
//     // Draw border
//     draw_minimap_border(game);
// }

void draw_minimap(t_game *game)
{
    int x, y;
    int tile_size = 5;  // Size of each map tile in pixels
    int map_x = 20;     // Minimap top-left corner x position
    int map_y = 20;     // Minimap top-left corner y position
    int max_width;      // Width of minimap in tiles
    t_rgb bg_color = {20, 20, 50};     // Background color (dark blue)
    t_rgb wall_color = {200, 200, 200}; // Wall color (light gray)
    t_rgb floor_color = {50, 50, 80};   // Floor color (medium blue)
    t_rgb player_color = {255, 50, 50}; // Player color (red)
    t_rgb sprite_color = {50, 255, 255}; // Sprite color (cyan)
    
    // Find the maximum width to ensure proper minimap dimensions
    max_width = 0;
    for (y = 0; y < game->config->map_count; y++)
    {
        int len = strlen(game->config->map[y]);
        if (len > max_width)
            max_width = len;
    }
    
    // Draw background for the minimap
    draw_simple_square(game, map_x - 5, map_y - 5, 
                      max_width * tile_size + 10, 
                      game->config->map_count * tile_size + 10, 
                      bg_color);
    
    // Draw the map tiles
    for (y = 0; y < game->config->map_count; y++)
    {
        for (x = 0; x < (int)strlen(game->config->map[y]); x++)
        {
            if (game->config->map[y][x] == '1')
            {
                // Draw a wall tile
                draw_simple_square(game, map_x + x * tile_size, map_y + y * tile_size, 
                                 tile_size, tile_size, wall_color);
            }
            else if (game->config->map[y][x] == '0' || 
                    game->config->map[y][x] == 'N' || 
                    game->config->map[y][x] == 'S' || 
                    game->config->map[y][x] == 'E' || 
                    game->config->map[y][x] == 'W')
            {
                // Draw a floor tile
                draw_simple_square(game, map_x + x * tile_size, map_y + y * tile_size, 
                                 tile_size, tile_size, floor_color);
            }
        }
    }
    
    // Draw sprites
    int i;
    for (i = 0; i < game->num_sprites; i++)
    {
        if (game->sprites[i].x >= 0 && game->sprites[i].y >= 0 &&
            game->sprites[i].y < game->config->map_count &&
            (int)game->sprites[i].x < (int)strlen(game->config->map[(int)game->sprites[i].y]))
        {
            // Draw a sprite
            draw_simple_square(game, map_x + (int)game->sprites[i].x * tile_size, 
                             map_y + (int)game->sprites[i].y * tile_size, 
                             tile_size, tile_size, sprite_color);
        }
    }
    
    // Draw player position
    draw_simple_square(game, map_x + (int)game->player.position.x * tile_size, 
                     map_y + (int)game->player.position.y * tile_size, 
                     tile_size, tile_size, player_color);
    
    // Draw player direction line
    int start_x = map_x + (int)game->player.position.x * tile_size + tile_size / 2;
    int start_y = map_y + (int)game->player.position.y * tile_size + tile_size / 2;
    int end_x = start_x + (int)(game->player.direction.x * tile_size * 2);
    int end_y = start_y + (int)(game->player.direction.y * tile_size * 2);
    
    // Draw a simple line for player direction
    int steps = 20; // Fixed number of steps for drawing the line
    for (i = 0; i < steps; i++)
    {
        int x = start_x + (end_x - start_x) * i / steps;
        int y = start_y + (end_y - start_y) * i / steps;
        my_mlx_pixel_put(&game->img, x, y, player_color);
    }
    
    // Draw border
    for (i = 0; i < max_width * tile_size + 10; i++)
    {
        // Top and bottom borders
        my_mlx_pixel_put(&game->img, map_x - 5 + i, map_y - 5, wall_color);
        my_mlx_pixel_put(&game->img, map_x - 5 + i, map_y + game->config->map_count * tile_size + 4, wall_color);
    }
    
    for (i = 0; i < game->config->map_count * tile_size + 10; i++)
    {
        // Left and right borders
        my_mlx_pixel_put(&game->img, map_x - 5, map_y - 5 + i, wall_color);
        my_mlx_pixel_put(&game->img, map_x + max_width * tile_size + 4, map_y - 5 + i, wall_color);
    }
}
