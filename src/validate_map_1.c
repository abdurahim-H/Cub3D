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

static int	is_set_char(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*trimmed;

	if (!s || !set)
		return (NULL);
	start = 0;
	while (s[start] && is_set_char(s[start], set))
		start++;
	end = ft_strlen(s);
	while (end > start && is_set_char(s[end - 1], set))
		end--;
	trimmed = malloc(end - start + 1);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start < end)
		trimmed[i++] = s[start++];
	trimmed[i] = '\0';
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
