/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:35 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:25 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_ray	init_ray_values(double ray_angle)
{
	t_ray	ray;

	ray.dir_x = cos(ray_angle);
	ray.dir_y = sin(ray_angle);
	ray.delta_x = fabs(1.0 / ray.dir_x);
	ray.delta_y = fabs(1.0 / ray.dir_y);
	return (ray);
}

t_dda	init_step_and_sidedist(t_ray ray, double px, double py)
{
	t_dda	dda;

	dda.map_x = (int)px;
	dda.map_y = (int)py;
	if (ray.dir_x < 0.0)
	{
		dda.step_x = -1;
		dda.side_x = (px - dda.map_x) * ray.delta_x;
	}
	else
	{
		dda.step_x = 1;
		dda.side_x = (dda.map_x + 1.0 - px) * ray.delta_x;
	}
	if (ray.dir_y < 0.0)
	{
		dda.step_y = -1;
		dda.side_y = (py - dda.map_y) * ray.delta_y;
	}
	else
	{
		dda.step_y = 1;
		dda.side_y = (dda.map_y + 1.0 - py) * ray.delta_y;
	}
	return (dda);
}

double correct_fisheye(double ray_angle, double player_angle, double perp_dist)
{
    double angle_diff = ray_angle - player_angle;
    // Ensure angle difference is within valid range
    while (angle_diff > M_PI) angle_diff -= 2 * M_PI;
    while (angle_diff < -M_PI) angle_diff += 2 * M_PI;
    
    // Prevent division by very small distances
    if (perp_dist < 0.1)  // Minimum distance to prevent stretching
        perp_dist = 0.1;
        
    return perp_dist * cos(angle_diff);
}
