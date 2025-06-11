/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:00 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:32 by aruckenb         ###   ########.fr       */
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
	slice_h = (int)(proj_dist / corr_dist);
	return (slice_h);
}

static void	set_bounds(int *start, int *end, int slice_h, t_game *game)
{
	*start = (game->win_y / 2) - (slice_h / 2);
	*end = *start + slice_h;
	if (*start < 0)
		*start = 0;
	if (*end >= game->win_y)
		*end = game->win_y - 1;
}

void	compute_wall_dimensions(t_game *game, double corr_dist,
		int *start, int *end)
{
	int	slice_h;

	slice_h = calculate_slice_height(game, corr_dist);
	set_bounds(start, end, slice_h, game);
}

t_texture	*select_wall_texture(t_game *game, t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
	{
		if (ray->dir_x > 0.0)
			return (&game->tex_east);
		else
			return (&game->tex_west);
	}
	if (ray->dir_y > 0.0)
		return (&game->tex_south);
	else
		return (&game->tex_north);
}

double	get_wall_x(t_game *game, t_ray *ray, t_dda *dda)
{
	double	wall_x;

	if (dda->side == 0)
		wall_x = game->py + dda->perp_dist * ray->dir_y;
	else
		wall_x = game->px + dda->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}
