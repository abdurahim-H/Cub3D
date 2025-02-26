#include "cub3d.h"

char	**collect_map_with_first_line(int fd, char *first_line,
	int *final_count)
{
	char	**temp_map;
	int		count;

	temp_map = NULL;
	count = 0;

	count = append_line_to_map(&temp_map, count, first_line);
	if (count < 0)
	{
		free(first_line);
		*final_count = 0;
		return (NULL);
	}

	*final_count = count;
	temp_map = collect_map_lines_rest(fd, final_count, temp_map);

	return (temp_map);
	}


void	calculate_map_dimensions(char **map, int map_count)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (i < map_count)
	{
		current_width = ft_strlen(trim_line(map[i])) - 1;
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	printf("\nMap dimensions: height = %d, width = %d\n",
		map_count, max_width);
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
