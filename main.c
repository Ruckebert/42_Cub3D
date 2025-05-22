/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:05:04 by aruckenb          #+#    #+#             */
/*   Updated: 2025/05/22 09:51:36 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"
#include <stdlib.h>

void	dummysetter(t_data *core)
{
	// r, g, b = 170, 187, 204
	core->top = 11189196;
	core->bottom = 11189196;
	
	//Put the image file here
	core->north = "~/Downloads/1.png";
	core->south = "~/Downloads/2.png";
	core->east = "~/Downloads/3.png";
	core->west = "~/Downloads/4.png";
	
	core->map = ft_calloc(sizeof(char *), 13);
	core->map[0] = "		1111111111111111111111111";
	core->map[1] = "		1000000000110000000000001";
	core->map[2] = "		1000000000110000000000001";
	core->map[3] = "		1001000000000000000000001";
	core->map[4] = "111111111011000001110000000000001";
	core->map[5] = "100000000011000001110111111111111";
	core->map[6] = "11110111111111011100000010001";
	core->map[7] = "11110111111111011101010010001";
	core->map[8] = "11000000110101011100000010001";
	core->map[9] = "10000000000000001100000010001";
	core->map[10] = "10000000000000001101010010001";
	core->map[11] = "11000001110101011111011110N0111";
	core->map[12] = "11110111 1110101 101111010001";
	core->map[13] = "11111111 1111111 111111111111";
	
}

void printer(t_data core, int count)
{
	ft_printf("Count: %d\n", count);
	ft_printf("Top: %d\n", core.top);
	ft_printf("Bottom: %d\n", core.bottom);
	ft_printf("North: %s\n", core.north);
	ft_printf("South: %s\n", core.south);
	ft_printf("East: %s\n", core.east);
	ft_printf("West: %s\n", core.west);
	if (core.map[0][0] != '\0')
	{
		int i = 0;
		while (core.map[i])
		{
			ft_printf("%s", core.map[i]);
			i++;
		}
	}
	ft_printf("\n");
} 

int main(int argc, char **argv)
{
	t_data core;
	//t_game game;

	ft_bzero(&core, sizeof(core));
	if (argc != 2)
	{
		write(2, "Error\nNot the correct amount of arguments\n", 43);
		return (-1);
	}
	//Checks if valid file
	if (ft_strlen(argv[1]) < 5 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4)	!= 0 || ft_strncmp(argv[1] + ft_strlen(argv[1]) - 5, "/.cub", 5) == 0)
	{
		write(2, "Error\nNot the correct amount of arguments\n", 43);
		return (-1);
	}

	int count = getdata(argv[1], &core, 0);
	if (count <= -1)
	{
		write(2, "Error\nGet Data Error!\n", 23);
		return (-1);
	}

	alllinkextractor(&core);
	core.map = get_map_char_len(count + 2, argv[1], &core);
	map_checker(&core);
	printer(core, count);

	//Here to free leaks
	if (core.map)
		free_array(core.map);
	if (core.north)
		free(core.north);
	if (core.south)
		free(core.south);
	if (core.east)
		free(core.east);
	if (core.west)
		free(core.west);
}
//	if (GetData(argv[1], &core) == -1)
//		return (1);
//	DummySetter(&core);
//	init(&core, &game);

