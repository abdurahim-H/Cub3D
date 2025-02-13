#include "cub3d.h"

void	init_config(t_config *cfg)
{
	cfg->width = -1;
	cfg->height = -1;
	cfg->tex_no = NULL;
	cfg->tex_so = NULL;
	cfg->tex_we = NULL;
	cfg->tex_ea = NULL;
	cfg->tex_s = NULL;
	cfg->floor_r = -1;
	cfg->floor_g = -1;
	cfg->floor_b = -1;
	cfg->ceiling_r = -1;
	cfg->ceiling_g = -1;
	cfg->ceiling_b = -1;
	cfg->map = NULL;
}
