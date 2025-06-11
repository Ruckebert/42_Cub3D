/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 09:24:20 by aruckenb          #+#    #+#             */
/*   Updated: 2025/06/11 09:28:18 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

void	validplayerdata(t_data *core)
{
	if (core->direction == '\0')
		error_exit(core, "Error\nInvalid Player Direction!\n");
	if (core->error >= 2)
		error_exit(core, "Error\nToo Many Player Icons!\n");
}

int	is_walkable(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\n')
		return (1);
	else
		return (0);
}

int	is_out_of_bounds(char **map, int i, int j)
{
	if (i < 0 || map[i] == NULL || j < 0 || j >= (int)ft_strlen(map[i]))
		return (1);
	else
		return (0);
}

void	assign_values(int dir[4][2])
{
	dir[0][0] = -1;
	dir[0][1] = 0;
	dir[1][0] = 1;
	dir[1][1] = 0;
	dir[2][0] = 0;
	dir[2][1] = -1;
	dir[3][0] = 0;
	dir[3][1] = 1;
}
