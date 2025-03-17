#include "cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player_direction_ns(t_game *game, char player_direction)
{
	if (player_direction == 'N')
	{
		game->player.direction.x = 0;
		game->player.direction.y = -1;
		game->player.camera_plane.x = -0.66;
		game->player.camera_plane.y = 0;
	}
	else if (player_direction == 'S')
	{
		game->player.direction.x = 0;
		game->player.direction.y = 1;
		game->player.camera_plane.x = 0.66;
		game->player.camera_plane.y = 0;
	}
}

static void	set_player_direction_ew(t_game *game, char player_direction)
{
	if (player_direction == 'E')
	{
		game->player.direction.x = 1;
		game->player.direction.y = 0;
		game->player.camera_plane.x = 0;
		game->player.camera_plane.y = 0.66;
	}
	else if (player_direction == 'W')
	{
		game->player.direction.x = -1;
		game->player.direction.y = 0;
		game->player.camera_plane.x = 0;
		game->player.camera_plane.y = -0.66;
	}
}

static void	set_player_direction(t_game *game, char player_direction)
{
	if (player_direction == 'N' || player_direction == 'S')
		set_player_direction_ns(game, player_direction);
	else if (player_direction == 'E' || player_direction == 'W')
		set_player_direction_ew(game, player_direction);
}

static void	setup_player(t_game *game, char player_direction,
		int row, size_t col)
{
	game->player.position.x = col + 0.5;
	game->player.position.y = row + 0.5;
	game->config->map[row][col] = '0';
	set_player_direction(game, player_direction);
	game->player.move_speed = 0.05;
	game->player.rot_speed = 0.03;
	game->player.vertical_offset = 0.0;
	game->player.vertical_limit = 300.0;
}

static int	find_player_position(t_game *game, char **map, int map_count)
{
	int		row;
	size_t	col;

	row = 0;
	while (row < map_count)
	{
		col = 0;
		while (map[row][col] != '\0')
		{
			if (is_player_char(map[row][col]))
			{
				setup_player(game, map[row][col], row, col);
				return (1);
			}
			col++;
		}
		row++;
	}
	return (0);
}

void	init_player(t_game *game)
{
	int	found;

	found = find_player_position(game, game->config->map,
			game->config->map_count);
	if (!found)
		exit_with_error("Player starting position not found", game->config);
}
