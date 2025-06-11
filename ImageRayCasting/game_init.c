/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:08 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:06 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	eval_keycode(int keycode, t_game *game, double *dx, double *dy)
{
	*dx = 0;
	*dy = 0;
	if (keycode == XK_w)
	{
		*dx = game->dir_x;
		*dy = game->dir_y;
	}
	else if (keycode == XK_s)
	{
		*dx = -game->dir_x;
		*dy = -game->dir_y;
	}
	else if (keycode == XK_d)
	{
		*dx = -game->dir_y;
		*dy = game->dir_x;
	}
	else if (keycode == XK_a)
	{
		*dx = game->dir_y;
		*dy = -game->dir_x;
	}
}

void	init_minimap(t_data *core, t_game *game)
{
	int	rows;
	int	cols;

	rows = map_height(core->map);
	cols = 0;
	while (core->map[0][cols])
		cols++;
	game->m_sq_size = 7;
	game->mini_w = cols * game->m_sq_size;
	game->mini_h = rows * game->m_sq_size;
	game->mini_off_x = 0;
	game->mini_off_y = 0;
}
