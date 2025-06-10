/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:00 by marsenij          #+#    #+#             */
/*   Updated: 2025/05/29 14:47:35 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	compute_wall_dimensions(t_game *game, double corr_dist,
			int *start, int *end, int *orig_start, int *wall_h)
{
	double	proj_dist;
	int		slice_h;

	proj_dist = (game->win_x / 2.0) / tan(FOV / 2.0);
	slice_h = (int)(proj_dist / corr_dist);
	*orig_start = (game->win_y / 2) - (slice_h / 2);
	*wall_h = slice_h;
	*start = *orig_start;
	*end = *start + slice_h;
	if (*start < 0)
		*start = 0;
	if (*end >= game->win_y)
		*end = game->win_y - 1;
}

t_texture	*select_wall_texture(t_game *game,
			t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
		return ((ray->dir_x > 0.0)
			? &game->tex_east
			: &game->tex_west);
	return ((ray->dir_y > 0.0)
		? &game->tex_south
		: &game->tex_north);
}

int	compute_texture_x(t_game *game, t_ray *ray,
			t_dda *dda, t_texture *tex)
{
	double	wall_x;
	int		tex_x;

	if (dda->side == 0)
		wall_x = game->py + dda->perp_dist * ray->dir_y;
	else
		wall_x = game->px + dda->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
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

t_wall_params	compute_wall_params(t_game *game,
			t_raycast_result *res)
{
	t_wall_params	p;

	compute_wall_dimensions(game,
		res->corrected_dist,
		&p.start,
		&p.end,
		&p.original_start,
		&p.wall_height);
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

void	draw_textured_wall(t_game *game, int col,
			t_wall_params *p)
{
	int	y;
	int	off;
	int	tex_y;

	y = p->start;
	while (y <= p->end)
	{
		off = y - p->original_start;
		tex_y = (off * p->tex->height) / p->wall_height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= p->tex->height)
			tex_y = p->tex->height - 1;
		my_mlx_pixel_put(game, col, y,
			get_texture_pixel(p->tex, p->tex_x, tex_y));
		y++;
	}
}
