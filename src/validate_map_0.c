#include "cub3d.h"

int	validate_top_row(char **map)
{
	int	i;

	i = 0;
	while (map[0][i] != '\0')
	{
		if (map[0][i] != '1')
		{
			fprintf(stderr, "Error: Top row invalid atposition %d: '%c'\n",
				i, map[0][i]);
			return (1);
		}
		i = i + 1;
	}
	return (0);
}

int	validate_bottom_row(char **map, int map_count)
{
	int	i;

	i = 0;
	while (map[map_count - 1][i] != '\0')
	{
		if (map[map_count - 1][i] != '1')
		{
			fprintf(stderr, "Error: Bottom row invalid at position %d: '%c'\n",
				i, map[map_count - 1][i]);
			return (1);
		}
		i = i + 1;
	}
	return (0);
}

int	validate_side_boundaries(char **map, int map_count)
{
	int	i;
	int	len;

	i = 1;
	while (i < map_count - 1)
	{
		if (map[i][0] != '1')
		{
			fprintf(stderr, "Error: Row %d does not start with a wall: '%c'\n",
				i, map[i][0]);
			return (1);
		}
		len = ft_strlen(map[i]);
		if (len > 0 && map[i][len - 1] != '1')
		{
			fprintf(stderr, "Error: Row %d does not end with a wall: '%c'\n",
				i, map[i][len - 1]);
			return (1);
		}
		i = i + 1;
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
