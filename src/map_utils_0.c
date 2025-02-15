#include "cub3d.h"

static int	is_line_blank_or_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	if (!line)
		return (0);
	if (is_line_blank_or_whitespace(line))
		return (0);
	if (line[0] != 'R' && line[0] != 'N' && line[0] != 'S'
		&& line[0] != 'W' && line[0] != 'E'
		&& line[0] != 'F' && line[0] != 'C')
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

char	**collect_map_lines_rest(int fd, int *map_count, char **map)
{
	char	*line;
	int		count;

	count = *map_count;
	while (1)
	{
		line = ft_getline(fd);
		if (line == NULL)
			break ;
		if (is_map_line(line))
		{
			count = append_line_to_map(&map, count, line);
			if (count < 0)
				return (NULL);
		}
		else
			free(line);
	}
	*map_count = count;
	return (map);
}
