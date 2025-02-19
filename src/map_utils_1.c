#include "cub3d.h"

char	**collect_map_with_first_line(int fd, char *first_line,
		int *final_count)
{
	char	**temp_map;
	int		count;
	int		newcount;

	temp_map = NULL;
	count = 0;
	newcount = append_line_to_map(&temp_map, count, first_line);
	if (newcount < 0)
	{
		free(first_line);
		return (NULL);
	}
	count = newcount;
	temp_map = collect_map_lines_rest(fd, &count, temp_map);
	*final_count = count;
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
		current_width = ft_strlen(map[i]) - 1;
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
