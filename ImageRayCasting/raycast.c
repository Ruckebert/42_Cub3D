/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:00:00 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/18 12:05:47 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static t_raycast_result	cast_single_ray(t_game *game, double ray_angle)
{
	t_raycast_result	r;

	r.ray = init_ray_values(ray_angle);
	r.dda = init_step_and_sidedist(r.ray, game->px, game->py);
	perform_dda(game, r.ray, &r.dda);
	r.corrected_dist = correct_fisheye(ray_angle,
			game->angle, r.dda.perp_dist);
	return (r);
}

void	process_column(t_game *game, int col, double ray_angle)
{
	t_raycast_result	r;
	t_wall_params		p;

	r = cast_single_ray(game, ray_angle);
	p = compute_wall_params(game, &r);
	draw_ceiling(game, col, p.start);
	draw_textured_wall(game, col, &p);
	draw_floor(game, col, p.end);
}

void	render_3d_projection(t_game *game)
{
	double	start_ang;
	double	step;
	double	fov;
	int		col;

	fov = M_PI / 3;
	start_ang = game->angle - (fov / 2.0);
	step = fov / (double)game->win_x;
	col = 0;
	while (col < game->win_x)
	{
		process_column(game, col, start_ang + col * step);
		col++;
	}
}

void	cast_ray_dda(t_game *game, double ray_angle)
{
	t_raycast_result	r;
	t_line_points		pts;
	int					ex;
	int					ey;

	r = cast_single_ray(game, ray_angle);
	ex = (int)((game->px + r.ray.dir_x * r.dda.perp_dist)
			* game->m_sq_size);
	ey = (int)((game->py + r.ray.dir_y * r.dda.perp_dist)
			* game->m_sq_size);
	pts.x0 = (int)(game->px * game->m_sq_size + game->m_sq_size / 2);
	pts.y0 = (int)(game->py * game->m_sq_size + game->m_sq_size / 2);
	pts.x1 = ex;
	pts.y1 = ey;
	draw_line(game, pts, 0x00FF00);
}
