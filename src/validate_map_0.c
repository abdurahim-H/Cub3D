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

int	is_set_char(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
