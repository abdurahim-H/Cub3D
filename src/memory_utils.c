#include "cub3d.h"

void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_config_resources(t_config *cfg)
{
	int	i;
	safe_free((void **)&cfg->tex_no);
	safe_free((void **)&cfg->tex_so);
	safe_free((void **)&cfg->tex_we);
	safe_free((void **)&cfg->tex_ea);
	safe_free((void **)&cfg->tex_s);
	if (cfg->map)
	{
		i = 0;
		while (i < cfg->map_count && cfg->map[i])
		{
			free(cfg->map[i]);
			i++;
		}
		free(cfg->map);
		cfg->map = NULL;
	}
}

void	exit_with_error(char *message, t_config *cfg)
{
	fprintf(stderr, "Error: %s\n", message);
	free_config_resources(cfg);
	exit(1);
}
