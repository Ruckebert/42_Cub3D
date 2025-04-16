/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:05:04 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/16 11:12:41 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

void	DummySetter(t_data *core)
{
	// r, g, b = 170, 187, 204
	core->Top = 11189196;
	core->Bottom = 11189196;
	
	//Put the image file here
	core->North = "";
	core->South = "";
	core->East = "";
	core->West = "";
	
	core->Map = ft_calloc(sizeof(char *), 13);
	core->Map[0] = "		1111111111111111111111111";
	core->Map[1] = "		1000000000110000000000001";
	core->Map[2] = "		1000000000110000000000001";
	core->Map[3] = "		1001000000000000000000001";
	core->Map[4] = "111111111011000001110000000000001";
	core->Map[5] = "100000000011000001110111111111111";
	core->Map[6] = "11110111111111011100000010001";
	core->Map[7] = "11110111111111011101010010001";
	core->Map[8] = "11000000110101011100000010001";
	core->Map[9] = "10000000000000001100000010001";
	core->Map[10] = "10000000000000001101010010001";
	core->Map[11] = "11000001110101011111011110N0111";
	core->Map[12] = "11110111 1110101 101111010001";
	core->Map[13] = "11111111 1111111 111111111111";
	
}

int main(int argc, char **argv)
{
	t_data core;

	ft_bzero(&core, sizeof(core));
	if (argc != 2)
	{
		write(2, "Not the correct amount of arguments\n", 37);
		//write(2, "Error\n", 37);
		return (-1);
	}
	if (GetData(argv[1], &core) == -1)
		return (-1);
	/*
	ft_printf("North: %s\n", core.North);
	ft_printf("South: %s\n", core.South);
	ft_printf("East: %s\n", core.East);
	ft_printf("West: %s\n", core.West);*/
}