/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:51:53 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/22 14:26:37 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
				exit(write(1, "Error\n", 6)); //Program should exit and free and state that an invlaid map
		}
		i++;
	}
}

void	validPlayerData(t_data *core)
{
	if (core->direction == '\0')
		exit(write(1, "Error\n", 6));
	if (core->error >= 2)
		exit(write(1, "Error\n", 6));
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
		{
			free(core->North);
			exit(write(1, "Error\nEmpty Space Line\n", 23));
		}
		count = 0;
		i++;
	}
}

void map_checker_borders(char **map, t_data *core)
{ //This function should check the size and any possible gaps
	int i;
	int j;
	int row_len;

	i = 0;
	while (map[i])
	{
		j = 0;
		row_len = ft_strlen(map[i]) - 2;
		//if (map[i + 1] == NULL)
		//	row_len++;
		while (map[i][j])
		{
			if (j == row_len || j == 0)
			{// This in theory checks the left most and right most side of the map
				if (map[i][j] == ' ')
				{
					int k = j;
					while (map[i][k] != '1')
					{
						if (map[i][k] == '0')
							exit(write(1, "Error\nEmpty Space Line\n", 23));
						k--;
					}
					if (map[i][k] != map[i + 1][k] && map[i][k] != map[i - 1][k])
					{
						free(core->North);
						exit(write(1, "Error\nEmpty Space Line\n", 23));
					}
				}
				//The issue with this is that it doesnt check whetehr or not the elements are also a space or null
				if (map[i][j] == map[i + 1][j] && map[i][j] == map[i - 1][j])
				{ //This checks whether the next elements from the row next and before contain the same element
					
					
				}
			}
			if (i == 0 || map[i + 1] == NULL)
			{//This should check the bottom and top of the maps
				
			}
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
				{
					free(core->North);
					exit(write(1, "Error\nTop and Bottom are Open!\n", 32));
				}
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
	//Check if the map is closed
}

/*
void	consumable(t_data *vars)
{
	int	num;

	num = 0;
	if (vars->map[vars->position_1][vars->position_2] == 'C')
	{
		vars->count++;
		vars->map[vars->position_1][vars->position_2] = '0';
	}
}

void	floodfill(t_data *vars, char **map, int x, int y)
{
	if (x < 0 || x >= vars->rows || y < 0 || y >= vars->cols
		|| map[x][y] == '1' || map[x][y] == 'F')
		return ;
	if (map[x][y] == 'C')
		vars->count++;
	else if (map[x][y] == 'E')
	{
		if (vars->count == vars->max_con)
			vars->exit_reachable = 1;
		return ;
	}
	map[x][y] = 'F';
	floodfill(vars, map, x + 1, y);
	floodfill(vars, map, x - 1, y);
	floodfill(vars, map, x, y + 1);
	floodfill(vars, map, x, y - 1);
}

int	floodfill_algor(t_data vars)
{
	char	**flood_map;
	int		i;

	flood_map = ft_calloc(vars.count, sizeof(char *));
	if (!flood_map)
		return (free_array(vars.map), 1);
	i = 0;
	while (i < vars.map_size - 2)
	{
		flood_map[i] = ft_strdup(vars.map[i]);
		if (!flood_map[i])
		{
			while (--i >= 0)
				free(flood_map[i]);
			return (free(flood_map), free_array(vars.map), 1);
		}
		i++;
	}
	vars.rows = vars.map_size - 2;
	vars.cols = ft_strlen(flood_map[0]);
	floodfill(&vars, flood_map, vars.cur_pos1, vars.cur_pos2);
	if (vars.exit_reachable == 0)
		return (free_array(flood_map), free_array(vars.map), 1);
	free_array(flood_map);
	return (0);
}*/
