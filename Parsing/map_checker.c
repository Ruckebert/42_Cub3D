/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:51:53 by aruckenb          #+#    #+#             */
/*   Updated: 2025/06/18 14:06:11 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	map_checker_tokens(char **map, t_data *core)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == ' '
					|| map[i][j] == '\n')
				j++;
			else if (map[i][j] == 'W' || map[i][j] == 'N' || map[i][j] == 'S'
					|| map[i][j] == 'E')
			{
				core->px = j;
				core->py = i;
				core->direction = map[i][j++];
				core->error++;
			}
			else
				error_exit(core, "Error\nInvalid Map!\n");
		}
		i++;
	}
}

void	check_surroundings(t_data *core, char **map, int i, int j)
{
	int		dir[4][2];
	int		d;
	int		ni;
	int		nj;
	char	neighbor;

	ft_bzero(dir, sizeof(dir));
	assign_values(dir);
	d = 0;
	while (d < 4)
	{
		ni = i + dir[d][0];
		nj = j + dir[d][1];
		if (is_out_of_bounds(map, ni, nj))
			error_exit(core, "Error\nOpen tile is Exposed!\n");
		neighbor = map[ni][nj];
		if (is_space(neighbor))
			error_exit(core, "Error\nOpen tile is Exposed!\n");
		d++;
	}
}

void	map_checker_borders(char **map, t_data *core)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_walkable(map[i][j]))
				check_surroundings(core, map, i, j);
			j++;
		}
		i++;
	}
}

void	map_checker_topbottom(char **map, t_data *core)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		if (i == 0 || map[i + 1] == NULL)
		{
			while (map[i][j])
			{
				if (map[i][j] == '0')
					error_exit(core, "Error\nTop and Bottom are Open!\n");
				j++;
			}
		}
		i++;
	}
}

void	map_checker(t_data *core)
{
	map_checker_tokens(core->map, core);
	validplayerdata(core);
	map_checker_topbottom(core->map, core);
	map_checker_borders(core->map, core);
}
