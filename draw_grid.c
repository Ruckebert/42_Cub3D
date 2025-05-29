/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:15 by marsenij          #+#    #+#             */
/*   Updated: 2025/05/29 14:32:28 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	draw_vertical_segment(t_game *game, int i, int j)
{
	int	x;
	int	y1;
	int	y2;

	x = game->mini_off_x + j * game->m_sq_size;
	y1 = game->mini_off_y + i * game->m_sq_size;
	y2 = y1 + game->m_sq_size;
	draw_line(game, x, y1, x, y2, 0x222222);
}

static void	process_vertical_lines(t_game *game, int i)
{
	int	cols;
	int	j;
	int	left;
	int	right;

	cols = ft_strlen(game->core->map[i]);
	j = 0;
	while (j <= cols)
	{
		left = tile_exists(game, i, j - 1);
		right = tile_exists(game, i, j);
		if (left || right)
			draw_vertical_segment(game, i, j);
		j++;
	}
}

void	draw_vertical_grid_lines(t_game *game)
{
	int	rows;
	int	i;

	rows = map_height(game->core->map);
	i = 0;
	while (i < rows)
	{
		process_vertical_lines(game, i);
		i++;
	}
}

static int	get_max_cols(t_game *game, int rows)
{
	int	max;
	int	i;
	int	cols;

	max = 0;
	i = 0;
	while (i < rows)
	{
		cols = ft_strlen(game->core->map[i]);
		if (cols > max)
			max = cols;
		i++;
	}
	return (max);
}

static void	draw_horizontal_segment(t_game *game, int i, int j)
{
	int	y;
	int	x1;
	int	x2;

	y = game->mini_off_y + i * game->m_sq_size;
	x1 = game->mini_off_x + j * game->m_sq_size;
	x2 = x1 + game->m_sq_size;
	draw_line(game, x1, y, x2, y, 0x222222);
}

static void	process_horizontal_lines(t_game *game, int i, int max_cols)
{
	int	j;
	int	top;
	int	bottom;

	j = 0;
	while (j < max_cols)
	{
		top = tile_exists(game, i - 1, j);
		bottom = tile_exists(game, i, j);
		if (top || bottom)
			draw_horizontal_segment(game, i, j);
		j++;
	}
}

void	draw_horizontal_grid_lines(t_game *game)
{
	int	rows;
	int	max_cols;
	int	i;

	rows = map_height(game->core->map);
	max_cols = get_max_cols(game, rows);
	i = 0;
	while (i <= rows)
	{
		process_horizontal_lines(game, i, max_cols);
		i++;
	}
}

void draw_grid(t_game *game)
{
    draw_vertical_grid_lines(game);
    draw_horizontal_grid_lines(game);
}