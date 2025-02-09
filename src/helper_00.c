#include "cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	has_cub_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4)
		return (0);
	return (ft_strcmp(filename + len - 4, ".cub") == 0);
}

int	is_save(char *s_argument)
{
	int	len;

	len = 0;
	while (s_argument[len])
		len++;
	if (len != 6)
		return (0);
	return (ft_strcmp(s_argument, "--save") == 0);
}

int	check_arg(int argc, char **argv)
{
	if ((argc <= 1 || argc > 3) || (!has_cub_extension(argv[1])))
	{
		printf("Error: incr arg. Usage: ./cub3D [map.cub] [--save]\n");
		return (1);
	}
	if (argv[2] && (!is_save(argv[2])))
	{
		printf("Error: incr arg. Usage: ./cub3D [map.cub] [--save]\n");
		return (1);
	}
	return (0);
}
