#include "cub3d.h"

int	is_map_line(char *line)
{
	if (!line || !*line)
		return (0);
	if (line[0] != 'R' && line[0] != 'N' && line[0] != 'S'
		&&line[0] != 'W' && line[0] != 'E' && line[0] != 'F'
		&&line[0] != 'C')
		return (1);
	return (0);
}

int	append_line_to_map(char ***map, int count, char *line)
{
	char	**new_map;

	new_map = ft_realloc(*map, sizeof(char *) * (count + 1));
	if (new_map == NULL)
		return (-1);
	*map = new_map;
	(*map)[count] = line;
	return (count + 1);
}

char	**collect_map_lines(int fd, int *map_count)
{
	char	**temp_map;
	char	*line;
	int		count;

	temp_map = NULL;
	count = 0;
	while (1)
	{
		line = ft_getline(fd);
		if (line == NULL)
			break ;
		if (is_map_line(line))
		{
			count = append_line_to_map(&temp_map, count, line);
			if (count < 0)
				return (NULL);
		}
		else
			free(line);
	}
	*map_count = count;
	return (temp_map);
}

void	print_map(char **map, int map_count)
{
	int	i;

	i = 0;
	while (i < map_count)
	{
		printf("%s", map[i]);
		i++;
	}
}

void	process_config(int fd, t_config *cfg)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = ft_getline(fd);
		if (line == NULL)
			break ;
		if (is_map_line(line))
		{
			free(line);
			break ;
		}
		parse_line(line, cfg);
		free(line);
	}
}
