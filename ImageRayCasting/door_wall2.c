/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_wall2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:01 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/18 13:35:41 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_orthogonally_adjacent(int px, int py, int x, int y)
{
	if ((abs(px - x) == 1 && py == y) || (abs(py - y) == 1 && px == x))
		return (1);
	return (0);
}

void	load_texture_data(t_game *game)
{
	game->tex_north.data = mlx_get_data_addr(game->tex_north.img,
			&game->tex_north.bpp, &game->tex_north.line_len,
			&game->tex_north.endian);
	game->tex_south.data = mlx_get_data_addr(game->tex_south.img,
			&game->tex_south.bpp, &game->tex_south.line_len,
			&game->tex_south.endian);
	game->tex_east.data = mlx_get_data_addr(game->tex_east.img,
			&game->tex_east.bpp, &game->tex_east.line_len,
			&game->tex_east.endian);
	game->tex_west.data = mlx_get_data_addr(game->tex_west.img,
			&game->tex_west.bpp, &game->tex_west.line_len,
			&game->tex_west.endian);
}
