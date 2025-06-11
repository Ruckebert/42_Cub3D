/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:15 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 10:32:04 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	draw_line(t_game *game, t_line_points pts, int color)
{
	t_line	line;
	int		i;

	init_line(&line, pts);
	if (line.steps == 0)
		return ;
	i = 0;
	while (i <= line.steps)
	{
		my_mlx_pixel_put(game, (int)line.x, (int)line.y, color);
		line.x += line.x_inc;
		line.y += line.y_inc;
		i++;
	}
}

int	tile_exists(t_game *game, int row, int col)
{
	int		rows;
	char	tile;
	int		cols;

	rows = map_height(game->core->map);
	if (row < 0 || row >= rows)
		return (0);
	cols = ft_strlen(game->core->map[row]);
	if (col < 0 || col >= cols)
		return (0);
	tile = game->core->map[row][col];
	return (tile != '\n' && tile != '\0');
}

void	draw_rays(t_game *game)
{
	double	start_angle;
	double	angle_step;
	double	ray_angle;
	int		i;
	double	fov;

	i = 0;
	fov = M_PI / 3;
	angle_step = fov / NUM_RAYS;
	start_angle = game->angle - (fov / 2);
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + i * angle_step;
		cast_ray_dda(game, ray_angle);
		i++;
	}
}

t_pos	get_player_screen_pos(t_game *game)
{
	t_pos	pos;

	pos.x = game->mini_off_x + (int)(game->px * game->m_sq_size);
	pos.y = game->mini_off_y + (int)(game->py * game->m_sq_size);
	return (pos);
}

int	minimap(t_game *game)
{
	draw_minimap(game);
	draw_grid(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
	return (0);
}
