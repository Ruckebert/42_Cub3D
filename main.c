/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:05:04 by aruckenb          #+#    #+#             */
/*   Updated: 2025/04/24 11:11:42 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"
#include <stdlib.h>

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

void printer(t_data core, int count)
{
	ft_printf("Count: %d\n", count);
	ft_printf("Top: %d\n", core.Top);
	ft_printf("Bottom: %d\n", core.Bottom);
	ft_printf("North: %s\n", core.North);
	ft_printf("South: %s\n", core.South);
	ft_printf("East: %s\n", core.East);
	ft_printf("West: %s\n", core.West);
	if (core.Map[0][0] != '\0')
	{
		int i = 0;
		while (core.Map[i])
		{
			ft_printf("%s", core.Map[i]);
			i++;
		}
	}
	ft_printf("\n");
}

int main(int argc, char **argv)
{
	t_data core;

	ft_bzero(&core, sizeof(core));
	if (argc != 2)
	{
		write(2, "Error\nNot the correct amount of arguments\n", 43);
		return (-1);
	}
	
	int count = GetData(argv[1], &core);
	if (count == -1)
	{
		write(2, "Error\nGet Data Error!\n", 23);
		return (-1);
	}
	AllLinkExtractor(&core);
	core.Map = get_map_char_len(count + 1, argv[1], &core);
	map_checker(&core);
	printer(core, count);

	
	//Here to free leaks
	if (core.Map)
		free_array(core.Map);
	if (core.North)
		free(core.North);
	if (core.South)
		free(core.South);
	if (core.East)
		free(core.East);
	if (core.West)
		free(core.West);
}
