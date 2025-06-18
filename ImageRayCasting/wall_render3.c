/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:00 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/18 12:12:03 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	calculate_slice_height(t_game *game, double corr_dist)
{
	double	proj_dist;
	int		slice_h;
	double	fov;

	fov = M_PI / 3;
	proj_dist = (game->win_x / 2.0) / tan(fov / 2.0);
	if (corr_dist < 0.0001)
		corr_dist = 0.0001;
	slice_h = (int)(proj_dist / corr_dist);
	return (slice_h);
}

int	compute_texture_x(t_game *game, t_ray *ray, t_dda *dda, t_texture *tex)
{
	double	wall_x;
	int		tex_x;

	wall_x = get_wall_x(game, ray, dda);
	tex_x = (int)(wall_x * tex->width);
	if ((dda->side == 0 && ray->dir_x < 0.0)
		|| (dda->side == 1 && ray->dir_y > 0.0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	offset;

	offset = y * tex->line_len + x * (tex->bpp / 8);
	return (*(int *)(tex->data + offset));
}

t_wall_params	compute_wall_params(t_game *game, t_raycast_result *res)
{
	t_wall_params	p;
	int				slice_h;

	slice_h = calculate_slice_height(game, res->corrected_dist);
	p.wall_height = slice_h;
	p.original_start = (game->win_y / 2) - (slice_h / 2);
	p.start = p.original_start;
	p.end = p.original_start + slice_h;
	if (p.start < 0)
		p.start = 0;
	if (p.end >= game->win_y)
		p.end = game->win_y - 1;
	p.tex = select_wall_texture(game, &res->ray, &res->dda);
	p.tex_x = compute_texture_x(game, &res->ray, &res->dda, p.tex);
	return (p);
}

void	draw_ceiling(t_game *game, int col, int start)
{
	int	y;

	y = 0;
	while (y < start)
	{
		my_mlx_pixel_put(game, col, y, game->core->top);
		y++;
	}
}
