#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

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
}	t_config;

typedef struct s_rgb
{
	int r;
	int g;
	int b;
}	t_rgb;

typedef struct s_header
{
	size_t	size;
}	t_header;

// general
int		ft_strcmp(const char *s1, const char *s2);
int		has_cub_extension(char *filename);
int		is_save(char *s_argument);
int		check_arg(int argc, char **argv);
void	init_config(t_config *cfg);
void	parse_line(char *line, t_config *cfg);
void	parse_resolution(char *line, t_config *cfg);
void	parse_north_texture(char *line, t_config *cfg);
void	parse_south_texture(char *line, t_config *cfg);
void	parse_west_texture(char *line, t_config *cfg);
void	parse_east_texture(char *line, t_config *cfg);
void	parse_sprite_texture(char *line, t_config *cfg);
void	parse_floor_texture(char *line, t_config *cfg);
t_rgb	parse_color(char *line, char prefix);
void	parse_floor_color(char *line, t_config *cfg);
void	parse_ceiling_color(char *line, t_config *cfg);
void	detect_type(char *line, t_config *cfg);
int		is_map_line(char *line);
char	**collect_map_lines(int fd, int *map_count);
void	print_map(char **map, int map_count);
void	process_config(int fd, t_config *cfg);
void	calculate_map_dimensions(char **map, int map_count);

// get_next_line
char	*ft_getline(int fd);
char	*ft_strdup_empty(void);
int		fill_leftover(int fd, char **leftover_ptr);
char	*finalize_leftover(char **leftover_ptr);

// helper funcitons
char	*ft_strdup_empty(void);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strsub(const char *s, unsigned int start, size_t len);
char	*ft_getline(int fd);
char	*cleanup_and_return_null(char **ptr);
int		ft_atoi(const char *str);
void	*ft_realloc(void *ptr, size_t new_size);


#endif