#include "cub3d.h"

char	**collect_map_with_first_line(
	int fd, int *map_count, char *first_line)
{
	char	**temp_map;
	int		count;
	int		ret;

	temp_map = NULL;
	count = 0;
	ret = append_line_to_map(&temp_map, count, first_line);
	if (ret < 0)
	{
		free(first_line);
		return (NULL);
	}
	count = ret;
	temp_map = collect_map_lines_rest(fd, &count);
	*map_count = count;
	return (temp_map);
}

void	process_config(int fd, t_config *cfg)
{
	char	*line;

	while (1)
	{
		line = ft_getline(fd);
		if (line == NULL)
			break ;
		if (is_map_line(line))
		{
			cfg->map = collect_map_with_first_line(fd, &((int){0}), line);
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

// void	calculate_map_dimensions(char **map, int map_count)
// {
// 	int	i;
// 	int	max_width;
// 	int	current_width;

// 	i = 0;
// 	max_width = 0;
// 	while (i < map_count)
// 	{
// 		current_width = ft_strlen(map[i]);
// 		if (current_width > max_width)
// 			max_width = current_width;
// 		i++;
// 	}
// 	printf("Map dimensions: height = %d, width = %d\n", map_count, max_width);
// }
