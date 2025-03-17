#include "cub3d.h"

void	trim_whitespace(char *str)
{
	int	len;

	if (!str)
		return ;
	len = strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n' || str[len - 1] == '\r'))
	{
		str[len - 1] = '\0';
		len--;
	}
}

void	trim_texture_paths(t_config *config)
{
	if (config->tex_no)
		trim_whitespace(config->tex_no);
	if (config->tex_so)
		trim_whitespace(config->tex_so);
	if (config->tex_we)
		trim_whitespace(config->tex_we);
	if (config->tex_ea)
		trim_whitespace(config->tex_ea);
	if (config->tex_s)
		trim_whitespace(config->tex_s);
}

void	print_texture_paths(t_config *config)
{
	printf("North texture: '%s'\n", config->tex_no);
	printf("South texture: '%s'\n", config->tex_so);
	printf("West texture: '%s'\n", config->tex_we);
	printf("East texture: '%s'\n", config->tex_ea);
	if (config->tex_s)
		printf("Sprite texture: '%s'\n", config->tex_s);
}