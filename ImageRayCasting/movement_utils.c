/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:01 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:18 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}

void	rotate_player(t_game *game, double delta)
{
	game->angle += delta;
	normalize_angle(&game->angle);
	game->dir_x = cos(game->angle);
	game->dir_y = sin(game->angle);
}

void	try_open_door(t_game *game, double x, double y)
{
	char	tile;
	int		map_x;
	int		map_y;

	map_x = (int)floor(x);
	map_y = (int)floor(y);
	tile = get_tile_at_pos(game->core->map, map_x, map_y);
	if (tile == '2')
		game->core->map[map_y][map_x] = '3';
}

int	can_move_to(t_game *game, double x, double y, double buffer)
{
	if (is_wall(game, x + buffer, y + buffer))
		return (0);
	if (is_wall(game, x + buffer, y - buffer))
		return (0);
	if (is_wall(game, x - buffer, y + buffer))
		return (0);
	if (is_wall(game, x - buffer, y - buffer))
		return (0);
	return (1);
}
