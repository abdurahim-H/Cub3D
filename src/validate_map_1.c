#include "cub3d.h"

int	is_allowed_char(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == '2'
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == '\n')
		return (1);
	return (0);
}

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
				fprintf(stderr, "Invalid map character: '%c' (ASCII: %d)\n",
					map[i][j], (int)map[i][j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static size_t	compute_trim_len(const char *s, const char *set)
{
	size_t	i;
	size_t	trim_len;

	i = 0;
	trim_len = 0;
	while (s[i] != '\0')
	{
		if (!is_set_char(s[i], set))
			trim_len++;
		i++;
	}
	return (trim_len);
}

char	*ft_strtrim(const char *s, const char *set)
{
	size_t	new_len;
	size_t	i;
	size_t	j;
	char	*trimmed;

	if (!s || !set)
		return (NULL);
	new_len = compute_trim_len(s, set);
	trimmed = malloc(new_len + 1);
	if (!trimmed)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (!is_set_char(s[i], set))
		{
			trimmed[j] = s[i];
			j++;
		}
		i++;
	}
	trimmed[j] = '\0';
	return (trimmed);
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
