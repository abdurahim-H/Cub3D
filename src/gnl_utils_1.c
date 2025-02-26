#include "cub3d.h"

char	*ft_strdup_empty(void)
{
	char	*empty_str;

	empty_str = malloc(sizeof(char));
	if (!empty_str)
		return (NULL);
	empty_str[0] = '\0';
	return (empty_str);
}

char	*cleanup_and_return_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

int	fill_leftover(int fd, char **leftover_ptr)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp;

	while (ft_strchr(*leftover_ptr, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*leftover_ptr, buffer);
		free(*leftover_ptr);
		*leftover_ptr = temp;
	}
	return (0);
}

char	*finalize_leftover(char **leftover_ptr)
{
	char	*line;

	if ((*leftover_ptr)[0] != '\0')
		line = ft_strdup(*leftover_ptr);
	else
		line = NULL;
	free(*leftover_ptr);
	*leftover_ptr = NULL;
	return (line);
}