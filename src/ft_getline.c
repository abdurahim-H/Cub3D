#include "cub3d.h"

char	*extract_and_update(char **leftover_ptr)
{
	char		*newline_ptr;
	size_t		line_length;
	char		*line;
	char		*temp;

	newline_ptr = ft_strchr(*leftover_ptr, '\n');
	if (newline_ptr != NULL)
	{
		line_length = newline_ptr - *leftover_ptr + 1;
		line = ft_strsub(*leftover_ptr, 0, line_length);
		temp = ft_strdup(newline_ptr + 1);
		free(*leftover_ptr);
		*leftover_ptr = temp;
		return (line);
	}
	return (NULL);
}

char	*ft_getline(int fd)
{
	static char		*leftover;
	char			*line;
	int				result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (leftover == NULL)
		leftover = ft_strdup_empty();
	result = fill_leftover(fd, &leftover);
	if (result < 0)
		return (cleanup_and_return_null(&leftover));
	if (ft_strchr(leftover, '\n') != NULL)
		line = extract_and_update(&leftover);
	else
		line = finalize_leftover(&leftover);
	return (line);
}