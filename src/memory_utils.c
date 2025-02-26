#include "cub3d.h"

// Safely free a pointer and set it to NULL
void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// Safe cleanup for all config resources
void	free_config_resources(t_config *cfg)
{
	int	i;

	// Free all texture paths
	safe_free((void **)&cfg->tex_no);
	safe_free((void **)&cfg->tex_so);
	safe_free((void **)&cfg->tex_we);
	safe_free((void **)&cfg->tex_ea);
	safe_free((void **)&cfg->tex_s);
	
	// Free map lines
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

// Exit with error message and cleanup
void	exit_with_error(char *message, t_config *cfg)
{
	fprintf(stderr, "Error: %s\n", message);
	free_config_resources(cfg);
	exit(1);
}