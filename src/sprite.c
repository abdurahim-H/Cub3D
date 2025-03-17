#include "cub3d.h"

int  count_sprites(char **map, int map_count)
{
    int i;
    int j;
    int count;

    count = 0;
    i = 0;
    while (i < map_count)
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '2')
                count++;
            j++;
        }
        i++;
    }
    return (count);
}

int initialize_sprites(t_game *game)
{
    int i;
    int j;
    int sprite_index;

    game->num_sprites = count_sprites(game->config->map, game->config->map_count);
    
    game->sprites = malloc(sizeof(t_sprite) * game->num_sprites);
    if (!game->sprites)
        return (1);
    
    game->zbuffer = malloc(sizeof(double) * game->config->width);
    if (!game->zbuffer)
    {
        free(game->sprites);
        game->sprites = NULL;
        return (1);
    }
    
    sprite_index = 0;
    i = 0;
    while (i < game->config->map_count)
    {
        j = 0;
        while (game->config->map[i][j])
        {
            if (game->config->map[i][j] == '2')
            {
                game->sprites[sprite_index].x = j + 0.5;
                game->sprites[sprite_index].y = i + 0.5;
                game->sprites[sprite_index].texture = 0;
                sprite_index++;
            }
            j++;
        }
        i++;
    }
    
    printf("Found %d sprites in map\n", game->num_sprites);
    return (0);
}

void calculate_sprite_distances(t_game *game)
{
    int i;

    i = 0;
    while (i < game->num_sprites)
    {
        double dx = game->player.position.x - game->sprites[i].x;
        double dy = game->player.position.y - game->sprites[i].y;
        
        game->sprites[i].distance = dx * dx + dy * dy;
        i++;
    }
}

int compare_sprites(const void *s1, const void *s2)
{
    t_sprite *sprite1 = (t_sprite *)s1;
    t_sprite *sprite2 = (t_sprite *)s2;
    
    if (sprite1->distance < sprite2->distance)
        return (1);
    else if (sprite1->distance > sprite2->distance)
        return (-1);
    return (0);
}

// int would_collide_with_sprite(t_game *game, double x, double y)
// {
//     int i;
//     double collision_distance;
//     double dx, dy, distance_squared;
    
//     if (!game->sprites || game->num_sprites <= 0)
//         return (0);
    
//     collision_distance = 0.3;
    
//     i = 0;
//     while (i < game->num_sprites)
//     {
//         dx = x - game->sprites[i].x;
//         dy = y - game->sprites[i].y;
        
//         distance_squared = dx * dx + dy * dy;
        
//         if (distance_squared < collision_distance * collision_distance)
//             return (1);
        
//         i++;
//     }
    
//     return (0);
// }

int would_collide_with_sprite(t_game *game, double x, double y)
{
    int i;
    double collision_distance;
    double dx, dy, distance_squared;
    
    // No collision if no sprites
    if (!game->sprites || game->num_sprites <= 0)
        return (0);
    
    // Set collision distance (radius around sprite where player can't enter)
    collision_distance = 0.3;  // Adjust this value to change collision sensitivity
    
    // Check distance to each sprite
    i = 0;
    while (i < game->num_sprites)
    {
        // Validate sprite coordinates to prevent segfault
        if (game->sprites[i].x < 0 || game->sprites[i].y < 0)
        {
            i++;
            continue;
        }
        
        dx = x - game->sprites[i].x;
        dy = y - game->sprites[i].y;
        
        // Calculate squared distance (faster than using sqrt)
        distance_squared = dx * dx + dy * dy;
        
        // If player is too close to a sprite, collision occurs
        if (distance_squared < collision_distance * collision_distance)
            return (1);
        
        i++;
    }
    
    return (0);
}

void sort_sprites(t_game *game)
{
    qsort(game->sprites, game->num_sprites, sizeof(t_sprite), compare_sprites);
}

void cleanup_sprites(t_game *game)
{
    if (game->sprites)
    {
        free(game->sprites);
        game->sprites = NULL;
    }
    
    if (game->zbuffer)
    {
        free(game->zbuffer);
        game->zbuffer = NULL;
    }
}
