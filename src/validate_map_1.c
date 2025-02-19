#include "cub3d.h"

int	is_allowed_char(char c)
{
	if (c == '0' || c == '1' || c == '2'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

// int	is_allowed_char(char c)
// {
//     if (c == ' ' || c == '0' || c == '1' || c == '2'
//         || c == 'N' || c == 'S' || c == 'E' || c == 'W')
//         return (1);
//     return (0);
// }


int	validate_map_characters(char **map, int map_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_count)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (!is_allowed_char(map[i][j]))
			{
				fprintf(stderr, "Invalid map character: '%c' (ASCII: %d)\n", map[i][j], (int)map[i][j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_map(char **map, int map_count)
{
	if (validate_map_characters(map, map_count) != 0)
	{
		fprintf(stderr, "Error: Invalid map characters detected.\n");
		return (1);
	}
	if (validate_map_boundaries(map, map_count) != 0)
	{
		fprintf(stderr, "Error: Map boundary check failed.\n");
		return (1);
	}
	if (validate_player_start(map, map_count) != 0)
		return (1);
	return (0);
}
