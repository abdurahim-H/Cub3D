#include "cub3d.h"

void	parse_resolution(char *line, t_config *cfg)
{
	int		width;
	int		height;
	char	*ptr;

	ptr = line;
	ptr++;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	width = ft_atoi(ptr);
	cfg->width = width;
	while (*ptr >= '0' && *ptr <= '9')
		ptr++;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	height = ft_atoi(ptr);
	cfg->height = height;
}

void	parse_north_texture(char *line, t_config *cfg)
{
	char	*ptr;

	ptr = line;
	ptr += 2;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	cfg->tex_no = ft_strdup(ptr);
}

void	parse_south_texture(char *line, t_config *cfg)
{
	char	*ptr;

	ptr = line;
	ptr += 2;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	cfg->tex_so = ft_strdup(ptr);
}

void	parse_west_texture(char *line, t_config *cfg)
{
	char	*ptr;

	ptr = line;
	ptr += 2;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	cfg->tex_we = ft_strdup(ptr);
}

void	parse_east_texture(char *line, t_config *cfg)
{
	char	*ptr;

	ptr = line;
	ptr += 2;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	cfg->tex_ea = ft_strdup(ptr);
}

static int	parse_int_component(const char **p_ptr)
{
	int			value;
	const char	*p;

	p = *p_ptr;
	while (*p == ' ' || *p == '\t')
		p++;
	value = ft_atoi(p);
	while (*p >= '0' && *p <= '9')
		p++;
	if (*p == ',')
		p++;
	while (*p == ' ' || *p == '\t')
		p++;
	*p_ptr = p;
	return (value);
}

t_rgb	parse_color(char *line, char prefix)
{
	t_rgb	color;
	char	*ptr;

	color.r = -1;
	color.g = -1;
	color.b = -1;
	ptr = line;
	if (*ptr != prefix)
		return (color);
	ptr++;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	color.r = parse_int_component((const char **)&ptr);
	color.g = parse_int_component((const char **)&ptr);
	color.b = parse_int_component((const char **)&ptr);
	return (color);
}

void	parse_sprite_texture(char *line, t_config *cfg)
{
	char	*ptr;

	ptr = line;
	ptr += 2;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	cfg->tex_s = ft_strdup(ptr);
}

void	parse_floor_color(char *line, t_config *cfg)
{
	t_rgb	color;

	color = parse_color(line, 'F');
	cfg->floor_r = color.r;
	cfg->floor_g = color.g;
	cfg->floor_b = color.b;
}

void	parse_ceiling_color(char *line, t_config *cfg)
{
	t_rgb	color;

	color = parse_color(line, 'C');
	cfg->ceiling_r = color.r;
	cfg->ceiling_g = color.g;
	cfg->ceiling_b = color.b;
}
