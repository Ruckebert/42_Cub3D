/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:15 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:00 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	draw_player_icon(t_game *game, t_pos pos, int size)
{
	fill_tile(game, pos, size, 0xFF0000);
}

void	draw_player_direction_arrow(t_game *game, t_pos center)
{
	t_line_points	pts;
	int				len;

	len = game->m_sq_size / 2;
	pts.x0 = center.x;
	pts.y0 = center.y;
	pts.x1 = center.x + (int)(game->dir_x * len);
	pts.y1 = center.y + (int)(game->dir_y * len);
	draw_line(game, pts, 0x0000FF);
}

void	draw_player(t_game *game)
{
	int		margin;
	int		size;
	t_pos	center;
	t_pos	icon;

	margin = game->m_sq_size / 4;
	size = game->m_sq_size - (2 * margin);
	center = get_player_screen_pos(game);
	icon.x = center.x - size / 2;
	icon.y = center.y - size / 2;
	draw_player_icon(game, icon, size);
	draw_player_direction_arrow(game, center);
}
