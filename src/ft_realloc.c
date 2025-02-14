#include "cub3d.h"

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

void	*ft_malloc(size_t size)
{
	t_header	*header;

	header = malloc(sizeof(t_header) + size);
	if (!header)
		return (NULL);
	header->size = size;
	return ((void *)(header + 1));
}

void	ft_free(void *ptr)
{
	t_header	*header;

	if (!ptr)
		return ;
	header = ((t_header *)ptr) - 1;
	free(header);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void		*new_ptr;
	size_t		old_size;
	t_header	*old_header;

	if (!ptr)
		return (ft_malloc(new_size));
	if (new_size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	old_header = ((t_header *)ptr) - 1;
	old_size = old_header->size;
	new_ptr = ft_malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	ft_free(ptr);
	return (new_ptr);
}
