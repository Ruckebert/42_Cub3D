/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:00 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/18 11:57:02 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../header.h"

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