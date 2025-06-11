/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:15 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:11 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->win_x || y < 0 || y >= game->win_y)
		return ;
	dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void	fill_tile(t_game *game, t_pos base, int tile_size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < tile_size)
	{
		x = 0;
		while (x < tile_size)
		{
			my_mlx_pixel_put(game, base.x + x, base.y + y, color);
			x++;
		}
		y++;
	}
}

int	get_tile_color(char map_tile)
{
	if (map_tile == '1')
		return (0xFFFFFF);
	if (map_tile == '2')
		return (0xFF0000);
	if (map_tile == '3')
		return (0x00FF00);
	if (map_tile == '\n')
		return (0x00000000);
	return (0x888888);
}

t_pos	get_minimap_pos(t_game *game, int grid_x, int grid_y)
{
	t_pos	pos;

	pos.x = game->mini_off_x + grid_x * game->m_sq_size;
	pos.y = game->mini_off_y + grid_y * game->m_sq_size;
	return (pos);
}

void	draw_minimap(t_game *game)
{
	int	rows;
	int	i;
	int	j;

	rows = map_height(game->core->map);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < (int)ft_strlen(game->core->map[i]))
		{
			if (game->core->map[i][j] != '\n')
				fill_tile(game,
					get_minimap_pos(game, j, i),
					game->m_sq_size,
					get_tile_color(game->core->map[i][j]));
			j++;
		}
		i++;
	}
}
