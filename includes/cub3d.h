#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <math.h>
#include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364

// --------------- Data Structures --------------- //
typedef struct s_config
{
	int		width;
	int		height;
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	char	*tex_s;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
	char	**map;
	int		map_count;
}	t_config;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_header
{
	size_t	size;
}	t_header;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	position;
	t_vector	direction;
	t_vector	camera_plane;
	double		move_speed;
	double		rot_speed;
	double vertical_offset;
	double vertical_limit;
}	t_player;

typedef struct s_input
{
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_left;
	int	key_right;
	int	key_up;
	int	key_down;
}	t_input;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	distance;
	int		texture;
}	t_sprite;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		tex_north;
	t_img		tex_south;
	t_img		tex_west;
	t_img		tex_east;
	t_img		tex_sprite;
	t_config	*config;
	t_player	player;
	t_input		input;
	t_sprite	*sprites;
    int			num_sprites;
    double		*zbuffer;
}	t_game;

typedef struct s_raycast
{
	t_vector	ray_dir;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	double		wall_x;
}	t_raycast;

typedef	struct s_draw_bounds
{
	int			start;
	int			end;
}	t_draw_bounds;



// --------------- General Utility Functions --------------- //
/* String comparison, file extension checking, argument validation,
	and string-to-integer conversion */
int		ft_strcmp(const char *s1, const char *s2);
int		has_cub_extension(char *filename);
int		is_save(char *s_argument);
int		check_arg(int argc, char **argv);
int		ft_atoi(const char *str);

// --------------- Config & Parsing Functions --------------- //
/* Configuration initialization, processing, and cleanup */
void	init_config(t_config *cfg);
void	process_config(int fd, t_config *cfg);
void	free_config_resources(t_config *cfg);

// --------------- Line Parsing Functions --------------- //
/* Parser for individual config file lines and ealement type detection */
void	parse_line(char *line, t_config *cfg);
void	detect_type(char *line, t_config *cfg);

// --------------- Texture & Setting Parser Functions --------------- //
/* Parser functions for textures, resolution, and colors */
void	parse_resolution(char *line, t_config *cfg);
void	parse_north_texture(char *line, t_config *cfg);
void	parse_south_texture(char *line, t_config *cfg);
void	parse_west_texture(char *line, t_config *cfg);
void	parse_east_texture(char *line, t_config *cfg);
void	parse_sprite_texture(char *line, t_config *cfg);
void	parse_floor_color(char *line, t_config *cfg);
void	parse_ceiling_color(char *line, t_config *cfg);
t_rgb	parse_color(char *line, char prefix);

// --------------- Map Handling Functions --------------- //
/* Map line detection, display, dimension calculation, and parsing */
int		is_map_line(char *line);
void	print_map(char **map, int map_count);
void	calculate_map_dimensions(char **map, int map_count);
int		parse_map(t_config *cfg, int fd, char *first_line);

// --------------- Map Validation Functions --------------- //
/* Functions to ensure map integrity, boundaries, and player position */
int		validate_map_characters(char **map, int map_count);
int		is_allowed_char(char c);
int		validate_top_row(char **map);
int		validate_bottom_row(char **map, int map_count);
int		validate_side_boundaries(char **map, int map_count);
int		validate_map_boundaries(char **map, int map_count);
int		count_player_positions(char **map, int map_count);
int		validate_player_start(char **map, int map_count);
int		validate_map(char **map, int map_count);
char	*ft_strtrim(const char *s, const char *set);
char	*trim_line(const char *line);
int		is_set_char(char c, const char *set);

// --------------- File Reading Functions (get_next_line) --------------- //
/* Line-by-line file reading implementation */
char	*ft_getline(int fd);
char	*ft_strdup_empty(void);
int		fill_leftover(int fd, char **leftover_ptr);
char	*finalize_leftover(char **leftover_ptr);
char	*extract_and_update(char **leftover_ptr);
char	*cleanup_and_return_null(char **ptr);

// --------------- String Helper Functions --------------- //
/* String length, joining, character finding, duplication,
	and substring extraction */
size_t	ft_strlen(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strsub(const char *s, unsigned int start, size_t len);
void	*ft_realloc(void *ptr, size_t new_size);

// --------------- Memory Utilities --------------- //
/* Safe memory freeing and error handling */
void	safe_free(void **ptr);
void	exit_with_error(char *message, t_config *cfg);

// --------------- Memory Management Functions --------------- //
/* Memory copying, allocation, and freeing utilities */
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

// --------------- Map Construction Functions --------------- //
/* Functions for building and collecting the map data */
int		append_line_to_map(char ***map, int count, char *line);
char	**collect_map_lines_rest(int fd, int *map_count, char **map);

// ------------- Game Initialization & Event Handling Functions ------------- //
/* Functions for initializing the game, handling key events,
	and closing the game */
int		init_game(t_game *game, t_config *config);
void	close_game(t_game *game);
int		handle_key(int keycode, t_game *game);
int		close_window(t_game *game);

// ------------- Player ------------- //
void	init_player(t_game *game);
void	move_forward(t_game *game, int diagonal);
void	move_backward(t_game *game, int diagonal);
void	move_left(t_game *game, int diagonal);
void	move_right(t_game *game, int diagonal);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	look_up(t_game *game);
void	look_down(t_game *game);

// Raycasting Functions
void	cast_rays(t_game *game);
void	calculate_ray_direction(t_game *game, int x, t_vector *ray_dir);
void	perform_dda(t_game *game, t_raycast *ray);
int		create_trgb(t_rgb color);
void	my_mlx_pixel_put(t_img *img, int x, int y, t_rgb color);
void	render(void *param);
int		render_loop(void *param);
// int render(void *param);

// int		render(void *param);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	process_input(t_game *game);

int load_texture(void *mlx, char *path, t_img *img);
int	load_textures(t_game *game);
t_img	*get_wall_texture(t_game *game, t_raycast *ray);
t_rgb	get_pixel_color(t_img *img, int x, int y);
void	draw_textured_line(t_game *game, int x, t_draw_bounds bounds, t_raycast *ray);

void	trim_whitespace(char *str);
void	trim_texture_paths(t_config *config);
void	print_texture_paths(t_config *config);

// --------------- Sprite Functions --------------- //
int     initialize_sprites(t_game *game);
void    calculate_sprite_distances(t_game *game);
void    sort_sprites(t_game *game);
void    render_sprites(t_game *game);
void    update_zbuffer(t_game *game, int x, double distance);
void    cleanup_sprites(t_game *game);
int would_collide_with_sprite(t_game *game, double x, double y);

int save_screenshot(t_game *game);

void draw_minimap(t_game *game);
void draw_transparent_rectangle(t_game *game, int x, int y, int width,
	int height, t_rgb color, int alpha);

#endif