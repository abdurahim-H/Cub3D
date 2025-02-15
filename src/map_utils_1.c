#include "cub3d.h"

char	**collect_map_with_first_line(int fd, char *first_line,
		int *final_count)
{
	char	**temp_map;
	int		count;
	int		newcount;

	temp_map = NULL;
	count = 0;
	newcount = append_line_to_map(&temp_map, count, first_line);
	if (newcount < 0)
	{
		free(first_line);
		return (NULL);
	}
	count = newcount;
	temp_map = collect_map_lines_rest(fd, &count, temp_map);
	*final_count = count;
	return (temp_map);
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

// void	process_config(int fd, t_config *cfg)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = ft_getline(fd);
// 		if (!line)
// 			break ;
// 		if (is_map_line(line))
// 		{
// 			cfg->map = collect_map_with_first_line(fd, line, &cfg->map_count);
// 			break ;
// 		}
// 		parse_line(line, cfg);
// 		free(line);
// 	}
// }

void	process_config(int fd, t_config *cfg)
{
	char	*line;

	while (1)
	{
		line = ft_getline(fd);
		if (!line)
			break ;
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (is_map_line(line))
		{
			if (!is_config_complete(cfg))
			{
				free(line);
				exit(1);
			}
			cfg->map = collect_map_with_first_line(fd, line, &cfg->map_count);
			break ;
		}
		parse_line(line, cfg);
		free(line);
	}
}

void	calculate_map_dimensions(char **map, int map_count)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (i < map_count)
	{
		current_width = ft_strlen(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	printf("Map dimensions: height = %d, width = %d\n",
		map_count, max_width);
}
