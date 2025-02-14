#include "cub3d.h"

void	parse_sprite_texture(char *line, t_config *cfg)
{
	char	*ptr;

	ptr = line;
	ptr += 2;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	cfg->tex_s = ft_strdup(ptr);
	printf("Parsed Sprite texture: %s\n", cfg->tex_s);
}

t_rgb	parse_color(char *line, char prefix)
{
	t_rgb	color;
	char	*ptr;

	ptr = line;
	if (*ptr != prefix)
		return (color);
	ptr++;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	color.r = ft_atoi(ptr);
	while (*ptr >= '0' && *ptr <= '9')
		ptr++;
	if (*ptr == ',')
		ptr++;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	color.g = ft_atoi(ptr);
	while (*ptr >= '0' && *ptr <= '9')
		ptr++;
	if (*ptr == ',')
		ptr++;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	color.b = ft_atoi(ptr);
	return (color);
}

void	parse_floor_color(char *line, t_config *cfg)
{
	t_rgb	color;

	color = parse_color(line, 'F');
	cfg->floor_r = color.r;
	cfg->floor_g = color.g;
	cfg->floor_b = color.b;
	printf("Parsed floor color: %d, %d, %d\n", cfg->floor_r,
		cfg->floor_g, cfg->floor_b);
}

void	parse_ceiling_color(char *line, t_config *cfg)
{
	t_rgb	color;

	color = parse_color(line, 'C');
	cfg->ceiling_r = color.r;
	cfg->ceiling_g = color.g;
	cfg->ceiling_b = color.b;
	printf("Parsed ceiling color: %d, %d, %d\n", cfg->ceiling_r,
		cfg->ceiling_g, cfg->ceiling_b);
}
