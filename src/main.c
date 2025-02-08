#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int	main(void)
{
    void	*mlx;
    void	*mlx_win;
    t_data	img;

    mlx = mlx_init();
    if (!mlx)
    {
        fprintf(stderr, "Failed to initialize MLX\n");
        return (1);
    }

    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    if (!mlx_win)
    {
        fprintf(stderr, "Failed to create window\n");
        return (1);
    }

    img.img = mlx_new_image(mlx, 1920, 1080);
    if (!img.img)
    {
        fprintf(stderr, "Failed to create image\n");
        return (1);
    }

    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                &img.endian);
    if (!img.addr)
    {
        fprintf(stderr, "Failed to get image data address\n");
        return (1);
    }

    my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);

    return (0);
}