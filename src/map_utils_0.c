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

static int	process_map_line(char *line, int count, int *gap_found, char ***map)
{
	if (is_line_blank_or_whitespace(line))
	{
		if (count > 0)
			*gap_found = 1;
		free(line);
		return (count);
	}
	if (*gap_found)
	{
		fprintf(stderr, "Error: Map has an empty line within it.\n");
		free(line);
		return (-1); // Signal an error
	}
	count = append_line_to_map(map, count, line);
	return (count);
}

static void	free_map_lines(char **map, int count)
{
	int	i;

	i = 0;
	if (!map)
		return;
	while (i < count)
	{
		if (map[i])
			free(map[i]);
		i++;
	}
}

char	**collect_map_lines_rest(int fd, int *map_count, char **map)
{
	char	*line;
	int		count;
	int		gap_found;

	count = *map_count;
	gap_found = 0;
	line = ft_getline(fd);
	while (line != NULL)
	{
		count = process_map_line(line, count, &gap_found, &map);
		if (count < 0)
		{
			// Simple and safe cleanup
			free_map_lines(map, *map_count);
			free(map);
			*map_count = 0;
			return (NULL);
		}
		line = ft_getline(fd);
	}
	*map_count = count;
	return (map);
}
