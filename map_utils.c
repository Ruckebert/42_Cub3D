/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:00:00 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/10 16:36:14 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	map_height(char **map)
{
	int	h;

	h = 0;
	if (!map)
		return (0);
	while (map[h])
		h++;
	return (h);
}

int	get_map_width(char **map, int y)
{
	if (!map || !map[y])
		return (0);
	return (ft_strlen(map[y]));
}

int	is_valid_map_pos(char **map, int x, int y)
{
	int	height;

	height = map_height(map);
	if (y < 0 || y >= height || !map[y])
		return (0);
	return (x >= 0 && x < get_map_width(map, y));
}

char	get_tile_at_pos(char **map, int x, int y)
{
	if (!is_valid_map_pos(map, x, y))
		return ('0');
	return (map[y][x]);
}
