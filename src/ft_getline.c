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

// char	*extract_and_update(char *leftover)
// {
// 	char		*newline_ptr;
// 	size_t		line_lenght;
// 	char		*line;
// 	char		*temp;

// 	newline_ptr = ft_strchr(leftover, '\n');
// 	if (newline_ptr != NULL)
// 	{
// 		line_lenght = newline_ptr - leftover + 1;
// 		line = ft_strsub(leftover, 0, line_lenght);
// 		temp = ft_strdup(newline_ptr + 1);
// 		free(leftover);
// 		leftover = temp;
// 		return (line);
// 	}
// 	return (leftover);
// }

// char	*ft_getline(int fd)
// {
// 	static char	*leftover;
// 	char		buffer[BUFFER_SIZE +1];
// 	int			bytes_read;
// 	char		*new_leftover;
// 	char		*line;

// 	if (fd < 0)
// 		return (NULL);
// 	if (leftover == NULL)
// 		leftover = ft_strdup_empty();
// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	if (bytes_read < 0)
// 		return (NULL);
// 	buffer[bytes_read] = '\0';
// 	new_leftover = ft_strjoin(leftover, buffer);
// 	free(leftover);
// 	leftover = new_leftover;
// 	line = extract_and_update(leftover);
// 	return (line);
// }

char	*cleanup_and_return_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return NULL;
}

int	fill_leftover(int fd, char **leftover_ptr)
{
	char buffer[BUFFER_SIZE + 1];
	int bytes_read;
	char *temp;

	while (ft_strchr(*leftover_ptr, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return -1;
		if (bytes_read == 0)
			break;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*leftover_ptr, buffer);
		free(*leftover_ptr);
		*leftover_ptr = temp;
	}
	return 0;
}

char	*finalize_leftover(char **leftover_ptr)
{
	char *line;

	if ((*leftover_ptr)[0] != '\0')
		line = ft_strdup(*leftover_ptr);
	else
		line = NULL;
	free(*leftover_ptr);
	*leftover_ptr = NULL;
	return line;
}

char	*extract_and_update(char **leftover_ptr)
{
	char *newline_ptr;
	size_t line_length;
	char *line;
	char *temp;

	newline_ptr = ft_strchr(*leftover_ptr, '\n');
	if (newline_ptr != NULL)
	{
		line_length = newline_ptr - *leftover_ptr + 1;
		line = ft_strsub(*leftover_ptr, 0, line_length);
		temp = ft_strdup(newline_ptr + 1);
		free(*leftover_ptr);
		*leftover_ptr = temp;
		return line;
	}
	return NULL;
}

char	*ft_getline(int fd)
{
	static char *leftover;
	char *line;
	int result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	if (leftover == NULL)
		leftover = ft_strdup_empty();
	result = fill_leftover(fd, &leftover);
	if (result < 0)
		return cleanup_and_return_null(&leftover);
	if (ft_strchr(leftover, '\n') != NULL)
		line = extract_and_update(&leftover);
	else
		line = finalize_leftover(&leftover);
	return line;
}
