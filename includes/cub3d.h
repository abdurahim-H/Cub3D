#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

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
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_config	*config;
	t_player	player;
}	t_game;

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
// void	player_position(t_vector position);
// void	player_direction(t_vector direction);
// void	player_camera_plane(t_vector camera_plane);
void	init_player(t_game *game);

#endif