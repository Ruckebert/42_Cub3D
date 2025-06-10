/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:01 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/10 16:44:00 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	update_door_state(t_game *game, int x, int y)
{
	char	tile;
	int		is_adjacent;
	int		player_x;
	int		player_y;

	player_x = (int)floor(game->px);
	player_y = (int)floor(game->py);
	tile = game->core->map[y][x];
	is_adjacent = is_orthogonally_adjacent(player_x, player_y, x, y);
	if (tile == '2' && is_adjacent)
		game->core->map[y][x] = '3';
	else if (tile == '3' && !is_adjacent)
		game->core->map[y][x] = '2';
}

static void	process_row(t_game *game, int y)
{
	int	width;
	int	x;

	if (!game->core->map[y])
		return ;
	width = get_map_width(game->core->map, y);
	x = 0;
	while (x < width)
	{
		update_door_state(game, x, y);
		x++;
	}
}

void	update_doors(t_game *game)
{
	int	height;
	int	y;

	if (!game || !game->core || !game->core->map)
		return ;
	height = map_height(game->core->map);
	y = 0;
	while (y < height)
	{
		process_row(game, y);
		y++;
	}
}

int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x);
	map_y = (int)floor(y);
	if (!is_valid_map_pos(game->core->map, map_x, map_y))
		return (1);
	if (game->core->map[map_y][map_x] == '1'
		|| game->core->map[map_y][map_x] == '2')
		return (1);
	return (0);
}
