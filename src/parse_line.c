#include "cub3d.h"

void	detect_type(char *line, t_config *cfg)
{
	if (line[0] == 'R')
		parse_resolution(line, cfg);
	else if (line[0] == 'N' && line[1] == 'O')
		parse_north_texture(line, cfg);
	else if (line[0] == 'S' && line[1] == 'O')
		parse_south_texture(line, cfg);
	else if (line[0] == 'W' && line[1] == 'E')
		parse_west_texture(line, cfg);
	else if (line[0] == 'E' && line[1] == 'A')
		parse_east_texture(line, cfg);
	else if (line[0] == 'S')
		parse_sprite_texture(line, cfg);
	else if (line[0] == 'F')
		parse_floor_color(line, cfg);
	else if (line[0] == 'C')
		parse_ceiling_color(line, cfg);
}

void	parse_line(char *line, t_config *cfg)
{
	if (line[0] == '\n' || line[0] == '\0')
		return ;
	detect_type(line, cfg);
}
