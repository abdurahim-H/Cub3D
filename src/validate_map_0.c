#include "cub3d.h"

char	*trim_line(const char *line)
{
	return (ft_strtrim(line, " \t"));
}

int	validate_top_row(char **map)
{
	char		*trimmed;
	size_t		i;

	trimmed = trim_line(map[0]);
	i = 0;
	while (i < ft_strlen(trimmed) - 1)
	{
		if (trimmed[i] != '1')
		{
			fprintf(stderr, "Error: Top row invalid at position %ld: '%c'\n",
				i, trimmed[i]);
			free(trimmed);
			return (1);
		}
		i++;
	}
	free(trimmed);
	return (0);
}

int	validate_bottom_row(char **map, int map_count)
{
	char	*trimmed;
	int		i;

	trimmed = trim_line(map[map_count - 1]);
	i = 0;
	while (trimmed[i] != '\0')
	{
		if (trimmed[i] != '1')
		{
			fprintf(stderr, "Error: Bottom row invalid at position %d: '%c'\n",
				i, trimmed[i]);
			free(trimmed);
			return (1);
		}
		i++;
	}
	free(trimmed);
	return (0);
}

int	validate_side_boundaries(char **map, int map_count)
{
	int		i;
	char	*trimmed;
	int		len;

	i = 1;
	while (i < map_count - 1)
	{
		trimmed = trim_line(map[i]);
		len = ft_strlen(trimmed) - 1;
		if (len > 0 && (trimmed[0] != '1' || trimmed[len - 1] != '1'))
		{
			if (trimmed[0] != '1')
				fprintf(stderr, "Error:Row %d does not start with wall: '%c'\n",
					i, trimmed[0]);
			else
				fprintf(stderr, "Error:Row %d does not end with wall: '%c'\n",
					i, trimmed[len - 1]);
			free(trimmed);
			return (1);
		}
		free(trimmed);
		i++;
	}
	return (0);
}

int	validate_map_boundaries(char **map, int map_count)
{
	int	top;
	int	bottom;
	int	sides;

	top = validate_top_row(map);
	if (top != 0)
		return (1);
	bottom = validate_bottom_row(map, map_count);
	if (bottom != 0)
		return (1);
	sides = validate_side_boundaries(map, map_count);
	if (sides != 0)
		return (1);
	return (0);
}
