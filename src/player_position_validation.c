#include "cub3d.h"

int	count_player_positions(char **map, int map_count)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < map_count)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
			{
				count = count + 1;
			}
			j = j + 1;
		}
		i = i + 1;
	}
	return (count);
}

int	validate_player_start(char **map, int map_count)
{
	int	count;

	count = count_player_positions(map, map_count);
	if (count != 1)
	{
		fprintf(stderr, "Error: 1 player start required; %d found.\n", count);
		return (1);
	}
	return (0);
}
