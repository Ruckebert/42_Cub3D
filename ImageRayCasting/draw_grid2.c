/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:15 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:36:57 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	get_max_cols(t_game *game, int rows)
{
	int	i;
	int	max;
	int	cols;

	i = 0;
	max = 0;
	while (i < rows)
	{
		cols = ft_strlen(game->core->map[i]);
		if (cols > max)
			max = cols;
		i++;
	}
	return (max);
}

void	draw_horizontal_segment(t_game *game, int i, int j)
{
	t_line_points	pts;
	int				y;
	int				x;

	y = game->mini_off_y + i * game->m_sq_size;
	x = game->mini_off_x + j * game->m_sq_size;
	pts.x0 = x;
	pts.y0 = y;
	pts.x1 = x + game->m_sq_size;
	pts.y1 = y;
	draw_line(game, pts, 0x222222);
}

void	process_horizontal_lines(t_game *game, int i, int max_cols)
{
	int	j;

	j = 0;
	while (j < max_cols)
	{
		if (tile_exists(game, i - 1, j) || tile_exists(game, i, j))
			draw_horizontal_segment(game, i, j);
		j++;
	}
}

void	draw_horizontal_grid_lines(t_game *game)
{
	int	i;
	int	rows;
	int	max_cols;

	rows = map_height(game->core->map);
	max_cols = get_max_cols(game, rows);
	i = 0;
	while (i <= rows)
	{
		process_horizontal_lines(game, i, max_cols);
		i++;
	}
}
