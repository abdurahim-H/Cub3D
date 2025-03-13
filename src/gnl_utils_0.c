#include "cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	total;
	char	*new_str;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total = len1 + len2;
	new_str = malloc(sizeof(char) * (total + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1 && *s1)
		new_str[i++] = *s1++;
	while (s2 && *s2)
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*dup;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

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
