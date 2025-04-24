/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:51:53 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/24 11:09:23 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

void map_checker_tokens(char **map, t_data *core)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1' || map[i][j] == '0' || map[i][j] == ' '|| map[i][j] == '\n')
				j++;
			else if (map[i][j] == 'W' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E')
			{
				core->px = j; //Check with Martin if this is correct
				core->py = i;
				core->direction = map[i][j];
				core->error++;
				j++;
			}
			else
				error_exit(core, "Error\nInvalid Map!\n");
		}
		i++;
	}
}

void	validPlayerData(t_data *core)
{
	if (core->direction == '\0')
		error_exit(core, "Error\nInvalid Player Direction!\n");
	if (core->error >= 2)
		error_exit(core, "Error\nToo Many Player Icons!\n");
}

void map_checker_spaces(char **map, t_data *core)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1' || map[i][j] == '0')
				count++;
			j++;
		}
		if (count == 0)
			error_exit(core, "Error\nEmpty Space Line!\n");
		count = 0;
		i++;
	}
}

int is_walkable(char c) 
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
    	return (0);
}

int is_space(char c) 
{
	if (c == ' ' || c == '\n')
		return (1);
	else
		return (0);
}

int is_out_of_bounds(char **map, int i, int j) 
{
	if (i < 0 || map[i] == NULL || j < 0 || j >= (int)ft_strlen(map[i]))
    	return (1);
	else
	 	return (0);
}

void check_surroundings(t_data *core, char **map, int i, int j) 
{
    int dir[4][2];
	
	ft_bzero(dir, sizeof(dir));
	dir[0][0] = -1;
	dir[0][1] = 0;

	dir[1][0] = 1;
	dir[1][1] = 0;

	dir[2][0] = 0;
	dir[2][1] = -1;

	dir[3][0] = 0;
	dir[3][1] = 1;

	int d = 0;
    while (d < 4)
	{
        int ni = i + dir[d][0];
        int nj = j + dir[d][1];

        if (is_out_of_bounds(map, ni, nj))
            error_exit(core, "Error\nOpen tile is Exposed!\n");
        
        char neighbor = map[ni][nj];

        if (is_space(neighbor))
            error_exit(core, "Error\nOpen tile is Exposed!\n");
		d++;
    }
}

void map_checker_borders(char **map, t_data *core) 
{
	int i = 0;
	int j = 0;
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

void map_checker_TopBottom(char **map, t_data *core)
{
	int i;
	int j;
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

void map_checker(t_data *core)
{
	if (core->Top == 0 || core->Bottom == 0)
		exit(write(1, "Error\nNo Top or Bottom\n", 23));
	map_checker_tokens(core->Map, core);
	validPlayerData(core);
	map_checker_spaces(core->Map, core);
	map_checker_TopBottom(core->Map, core);
	map_checker_borders(core->Map, core);
}
