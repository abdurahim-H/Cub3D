#include "cub3d.h"

void write_int_to_buffer(unsigned char *buffer, int value)
{
    buffer[0] = (unsigned char)(value);
    buffer[1] = (unsigned char)(value >> 8);
    buffer[2] = (unsigned char)(value >> 16);
    buffer[3] = (unsigned char)(value >> 24);
}


void write_short_to_buffer(unsigned char *buffer, short value)
{
    buffer[0] = (unsigned char)(value);
    buffer[1] = (unsigned char)(value >> 8);
}

void create_bmp_file_header(int file_size, unsigned char *buffer)
{
    buffer[0] = 'B';
    buffer[1] = 'M';
    write_int_to_buffer(buffer + 2, file_size);
    write_int_to_buffer(buffer + 6, 0);  // Reserved
    write_int_to_buffer(buffer + 10, 54); // Offset to pixel data
}

void create_bmp_info_header(int width, int height, unsigned char *buffer)
{
    write_int_to_buffer(buffer + 0, 40);  // Size of info header
    write_int_to_buffer(buffer + 4, width);
    write_int_to_buffer(buffer + 8, height);
    write_short_to_buffer(buffer + 12, 1);  // Color planes
    write_short_to_buffer(buffer + 14, 24); // Bits per pixel (24 for RGB)
    write_int_to_buffer(buffer + 16, 0);    // No compression
    write_int_to_buffer(buffer + 20, 0);    // Image size (can be 0 for RGB)
    write_int_to_buffer(buffer + 24, 0);    // Horizontal resolution
    write_int_to_buffer(buffer + 28, 0);    // Vertical resolution
    write_int_to_buffer(buffer + 32, 0);    // Colors in color table
    write_int_to_buffer(buffer + 36, 0);    // Important color count
}


int get_color_from_img(t_img *img, int x, int y)
{
    char *pixel;
    int offset;
    
    offset = y * img->line_length + x * (img->bits_per_pixel / 8);
    pixel = img->addr + offset;
    
    // Return color as RGB integer
    return (*(int *)pixel) & 0xFFFFFF;
}

int save_screenshot(t_game *game)
{
    int fd;
    int width;
    int height;
    int row_size;
    int file_size;
    int padding_size;
    unsigned char bmp_file_header[14];
    unsigned char bmp_info_header[40];
    unsigned char padding[3];
    int x, y, color;
    
    width = game->config->width;
    height = game->config->height;
    
    // Calculate row size with padding (rows must be multiple of 4 bytes)
    padding_size = (4 - ((width * 3) % 4)) % 4;
    row_size = width * 3 + padding_size;
    file_size = 54 + (row_size * height);  // Headers + pixel data
    
    // Create file
    fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        fprintf(stderr, "Error: Failed to create screenshot file\n");
        return (1);
    }
    
    // Initialize padding with zeros
    padding[0] = 0;
    padding[1] = 0;
    padding[2] = 0;
    
    // Create and write headers
    create_bmp_file_header(file_size, bmp_file_header);
    create_bmp_info_header(width, height, bmp_info_header);
    write(fd, bmp_file_header, 14);
    write(fd, bmp_info_header, 40);
    
    // Write pixel data (bottom to top, left to right)
    y = height - 1;
    while (y >= 0)
    {
        x = 0;
        while (x < width)
        {
            color = get_color_from_img(&game->img, x, y);
            
            // Write pixel data in BGR format (BMP stores colors as BGR)
            write(fd, &color, 3);
            x++;
        }
        
        // Write padding if needed
        if (padding_size > 0)
            write(fd, padding, padding_size);
        
        y--;
    }
    
    close(fd);
    printf("Screenshot saved as screenshot.bmp\n");
    return (0);
}
