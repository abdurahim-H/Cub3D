#include "cub3d.h"

int	create_trgb(t_rgb color)
{
	return (0 << 24 | color.r << 16 | color.g << 8 | color.b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, t_rgb color)
{
	char	*addr;
	int		offset;
	int		color_value;

	if (x < 0 || y < 0)
		return ;
	offset = y * img->line_length + x * (img->bits_per_pixel / 8);
	addr = img->addr + offset;
	color_value = create_trgb(color);
	*(unsigned int *)addr = color_value;
}
