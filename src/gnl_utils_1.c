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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			copy_size = old_size;
		else
			copy_size = new_size;
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
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
