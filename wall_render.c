/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:00 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/10 16:59:16 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_floor(t_game *game, int col, int end)
{
	int	y;

	y = end + 1;
	while (y < game->win_y)
	{
		my_mlx_pixel_put(game, col, y, game->core->bottom);
		y++;
	}
}

static int	calculate_tex_y(int y, t_wall_params *p)
{
	int	off;
	int	tex_y;

	off = y - p->original_start;
	tex_y = (off * p->tex->height) / p->wall_height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= p->tex->height)
		tex_y = p->tex->height - 1;
	return (tex_y);
}

void	draw_textured_wall(t_game *game, int col, t_wall_params *p)
{
	int	y;
	int	tex_y;

	y = p->start;
	while (y <= p->end)
	{
		tex_y = calculate_tex_y(y, p);
		my_mlx_pixel_put(game, col, y,
			get_texture_pixel(p->tex, p->tex_x, tex_y));
		y++;
	}
}
