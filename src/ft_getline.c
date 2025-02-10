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

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i =0;
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

char	*ft_getline(int fd)
{
	static char	*leftover;
	char		buffer[BUFFER_SIZE +1];
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	if (leftover == NULL)
		leftover = ft_strdup_empty();
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	return (leftover);
}
