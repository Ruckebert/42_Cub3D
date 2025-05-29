/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:15 by marsenij          #+#    #+#             */
/*   Updated: 2025/05/29 15:20:04 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_line(t_line *line, t_line_points pts)
{
	line->dx = pts.x1 - pts.x0;
	line->dy = pts.y1 - pts.y0;
	line->x = pts.x0;
	line->y = pts.y0;
	if (abs(line->dx) > abs(line->dy))
		line->steps = abs(line->dx);
	else
		line->steps = abs(line->dy);
	if (line->steps == 0)
	{
		line->x_inc = 0;
		line->y_inc = 0;
	}
	else
	{
		line->x_inc = (float)line->dx / line->steps;
		line->y_inc = (float)line->dy / line->steps;
	}
}
