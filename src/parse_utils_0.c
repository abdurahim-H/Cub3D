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
