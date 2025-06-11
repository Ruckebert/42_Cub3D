/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:15 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:36:54 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	draw_vertical_segment(t_game *game, int i, int j)
{
	t_line_points	pts;
	int				x;
	int				y;

	x = game->mini_off_x + j * game->m_sq_size;
	y = game->mini_off_y + i * game->m_sq_size;
	pts.x0 = x;
	pts.y0 = y;
	pts.x1 = x;
	pts.y1 = y + game->m_sq_size;
	draw_line(game, pts, 0x222222);
}

static void	process_vertical_lines(t_game *game, int i)
{
	int	j;
	int	cols;

	cols = ft_strlen(game->core->map[i]);
	j = 0;
	while (j <= cols)
	{
		if (tile_exists(game, i, j - 1) || tile_exists(game, i, j))
			draw_vertical_segment(game, i, j);
		j++;
	}
}

void	draw_vertical_grid_lines(t_game *game)
{
	int	i;
	int	rows;

	rows = map_height(game->core->map);
	i = 0;
	while (i < rows)
	{
		process_vertical_lines(game, i);
		i++;
	}
}

void	draw_grid(t_game *game)
{
	draw_vertical_grid_lines(game);
	draw_horizontal_grid_lines(game);
}
