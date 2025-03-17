#include "cub3d.h"
#include <mlx.h>

// int	main(int argc, char **argv)
// {
// 	int			fd;
// 	t_config	config;
// 	t_game		game;

// 	fd = 0;
// 	if (check_arg(argc, argv) != 0)
// 		return (1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	init_config(&config);
// 	process_config(fd, &config);
	
// 	// Add this line to trim all texture paths
// 	trim_texture_paths(&config);
	
// 	// Optional: Add this line for debugging
// 	// print_texture_paths(&config);
	
// 	if (!config.map)
// 	{
// 		fprintf(stderr, "Error: No valid map found\n");
// 		free_config_resources(&config);
// 		close(fd);
// 		exit(1);
// 	}
// 	if (validate_map(config.map, config.map_count) != 0)
// 	{
// 		free_config_resources(&config);
// 		close(fd);
// 		exit(1);
// 	}
// 	print_map(config.map, config.map_count);
// 	calculate_map_dimensions(config.map, config.map_count);
// 	close(fd);
// 	if (init_game(&game, &config) != 0)
// 	{
// 		fprintf(stderr, "Error: Failed to initialize game\n");
// 		free_config_resources(&config);
// 		exit(1);
// 	}
// 	printf("Player initial position: (%f, %f)\n", game.player.position.x, game.player.position.y);
// 	printf("Player initial direction: (%f, %f)\n", game.player.direction.x, game.player.direction.y);
	
// 	mlx_loop(game.mlx);
// 	close_game(&game);
// 	free_config_resources(&config);
// 	return (0);
// }

int main(int argc, char **argv)
{
    int         fd;
    t_config    config;
    t_game      game;
    int         save_mode;

    fd = 0;
    save_mode = 0;
    
    if (check_arg(argc, argv) != 0)
        return (1);
    
    // Check if running in save mode
    save_mode = (argc == 3 && is_save(argv[2]));
    
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }
    
    // Initialize and process configuration
    init_config(&config);
    process_config(fd, &config);
    close(fd);
    
    // Trim texture paths to remove any trailing whitespace
    trim_texture_paths(&config);
    
    // Validate map
    if (!config.map)
    {
        fprintf(stderr, "Error: No valid map found\n");
        free_config_resources(&config);
        exit(1);
    }
    
    if (validate_map(config.map, config.map_count) != 0)
    {
        free_config_resources(&config);
        exit(1);
    }
    
    print_map(config.map, config.map_count);
    calculate_map_dimensions(config.map, config.map_count);
    
    // Initialize MLX (common for both modes)
    game.config = &config;
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        fprintf(stderr, "Error: Failed to initialize MLX\n");
        free_config_resources(&config);
        exit(1);
    }
    
    // Create window only if not in save mode
    if (!save_mode)
    {
        game.win = mlx_new_window(game.mlx, config.width, config.height, "Cub3D");
        if (!game.win)
        {
            fprintf(stderr, "Error: Failed to create window\n");
            free_config_resources(&config);
            exit(1);
        }
    }
    else
    {
        game.win = NULL;
    }
    
    // Create image buffer (common for both modes)
    game.img.img = mlx_new_image(game.mlx, config.width, config.height);
    if (!game.img.img)
    {
        fprintf(stderr, "Error: Failed to create image buffer\n");
        if (game.win)
            mlx_destroy_window(game.mlx, game.win);
        free_config_resources(&config);
        exit(1);
    }
    
    game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
            &game.img.line_length, &game.img.endian);
    
    // Initialize sprites
    game.sprites = NULL;
    game.num_sprites = 0;
    game.zbuffer = NULL;
    
    // Load textures
    if (load_textures(&game))
    {
        fprintf(stderr, "Error: Failed to load textures\n");
        close_game(&game);
        free_config_resources(&config);
        exit(1);
    }
    
    // Initialize sprites
    if (initialize_sprites(&game))
    {
        fprintf(stderr, "Error: Failed to initialize sprites\n");
        close_game(&game);
        free_config_resources(&config);
        exit(1);
    }
    
    // Initialize player
    init_player(&game);
    
    // Save mode: render one frame, save, and exit
    if (save_mode)
    {
        // Set up input to initial state
        game.input = (t_input){0, 0, 0, 0, 0, 0, 0, 0};
        
        // Render one frame
        render(&game);
        
        // Save screenshot
        save_screenshot(&game);
        printf("Screenshot saved to screenshot.bmp\n");
        
        // Clean up and exit
        close_game(&game);
        free_config_resources(&config);
        return (0);
    }
    
    // Normal mode: set up event hooks and enter game loop
    game.input = (t_input){0, 0, 0, 0, 0, 0, 0, 0};
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game);
    mlx_hook(game.win, 17, 1L << 17, close_window, &game);
    mlx_loop_hook(game.mlx, render_loop, &game);
    
    printf("Player initial position: (%f, %f)\n", game.player.position.x, game.player.position.y);
    printf("Player initial direction: (%f, %f)\n", game.player.direction.x, game.player.direction.y);
    
    mlx_loop(game.mlx);
    close_game(&game);
    free_config_resources(&config);
    
    return (0);
}
