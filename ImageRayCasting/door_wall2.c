/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_wall2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:01 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:36:49 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_orthogonally_adjacent(int px, int py, int x, int y)
{
	if ((abs(px - x) == 1 && py == y) || (abs(py - y) == 1 && px == x))
		return (1);
	return (0);
}

void	init_direction_arrays(int dx[4], int dy[4])
{
	dx[0] = 0;
	dx[1] = 1;
	dx[2] = 0;
	dx[3] = -1;
	dy[0] = -1;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = 0;
}

int	check_adjacent_tiles(t_game *game, int player_x, int player_y)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	check_x;
	int	check_y;

	init_direction_arrays(dx, dy);
	i = 0;
	while (i < 4)
	{
		check_x = player_x + dx[i];
		check_y = player_y + dy[i];
		if (get_tile_at_pos(game->core->map, check_x, check_y) == '2')
			return (1);
		i++;
	}
	return (0);
}
