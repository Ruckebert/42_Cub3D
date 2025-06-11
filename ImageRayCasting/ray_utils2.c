/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:35 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:27 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static int	get_map_dimensions(char **map, int y, int *height)
{
	if (y == 0)
	{
		*height = 0;
		while (map[*height])
			(*height)++;
	}
	if (map == NULL || map[y] == NULL)
		return (0);
	return ((int)ft_strlen(map[y]));
}

void	update_dda(t_ray ray, t_dda *dda)
{
	if (dda->side_x < dda->side_y)
	{
		dda->side_x += ray.delta_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_y += ray.delta_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
}

void	perform_dda(t_game *game, t_ray ray, t_dda *dda)
{
	int		hit;
	int		depth;
	int		map_h;
	char	t;

	hit = 0;
	depth = MAX_DEPTH;
	map_h = 0;
	get_map_dimensions(game->core->map, 0, &map_h);
	while (!hit && depth-- > 0)
	{
		update_dda(ray, dda);
		if (!is_valid_map_pos(game->core->map, dda->map_x, dda->map_y))
			break ;
		t = game->core->map[dda->map_y][dda->map_x];
		if (t == '1' || t == '2')
			hit = 1;
	}
	if (dda->side == 0)
		dda->perp_dist = dda->side_x - ray.delta_x;
	else
		dda->perp_dist = dda->side_y - ray.delta_y;
}
