#include "cub3d.h"

void	init_config(t_config *cfg)
{
	cfg->width = -1;
	cfg->height = -1;
	cfg->tex_no = NULL;
	cfg->tex_so = NULL;
	cfg->tex_we = NULL;
	cfg->tex_ea = NULL;
	cfg->tex_s = NULL;
	cfg->floor_r = -1;
	cfg->floor_g = -1;
	cfg->floor_b = -1;
	cfg->ceiling_r = -1;
	cfg->ceiling_g = -1;
	cfg->ceiling_b = -1;
	cfg->map = NULL;
	cfg->map_count = 0;
}

static int	is_config_complete(t_config *cfg)
{
	if (cfg->width == -1 || cfg->height == -1)
		return (0);
	if (!cfg->tex_no || !cfg->tex_so || !cfg->tex_we
		|| !cfg->tex_ea || !cfg->tex_s)
		return (0);
	if (cfg->floor_r == -1 || cfg->floor_g == -1 || cfg->floor_b == -1)
		return (0);
	if (cfg->ceiling_r == -1 || cfg->ceiling_g == -1 || cfg->ceiling_b == -1)
		return (0);
	return (1);
}

void	process_config(int fd, t_config *cfg)
{
	char	*line;

	while (1)
	{
		line = ft_getline(fd);
		if (!line)
			exit_with_error("Unexpected end of file", cfg);
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue;
		}
		if (is_map_line(line))
		{
			if (!is_config_complete(cfg))
			{
				free(line);
				exit_with_error("Incomplete configuration before map", cfg);
			}
			if (parse_map(cfg, fd, line) < 0)
				exit_with_error("Failed to parse map", cfg);
			break;
		}
		printf("%s", line);
		parse_line(line, cfg);
		free(line);
	}
}
