/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:05:04 by aruckenb          #+#    #+#             */
/*   Updated: 2025/06/18 15:47:47 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

/*void printer(t_data core, int count)
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
}*/
int	on_window_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	on_destroy(game);
	return (0);
}

void	core_image(t_data core, t_game game, int count, char **argv)
{
	alllinkextractor(&core);
	core.map = get_map_char_len(count + 2, argv[1], &core);
	map_checker(&core);
	game.px = core.px;
	game.py = core.py;
	if (init(&core, &game) == 1)
	{
		on_destroy(&game);
		return ;
	}
	render(&game);
	mlx_loop_hook(game.mlx_ptr, (void *)render, &game);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &on_key_press, &game);
	mlx_hook(game.win_ptr, DestroyNotify, StructureNotifyMask,
		&on_window_close, &game);
	mlx_loop(game.mlx_ptr);
}

int	main(int argc, char **argv)
{
	int		count;
	t_data	core;
	t_game	game;

	ft_bzero(&core, sizeof(core));
	ft_bzero(&game, sizeof(game));
	if (argc != 2)
	{
		write(2, "Error\nNot the correct amount of arguments\n", 43);
		return (-1);
	}
	if (ft_strlen(argv[1]) < 5
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0
		|| ft_strncmp(argv[1] + ft_strlen(argv[1]) - 5, "/.cub", 5) == 0)
	{
		write(2, "Error\nNot the correct amount of arguments\n", 43);
		return (-1);
	}
	count = getdata(argv[1], &core, 0);
	if (count <= -1)
		error_exit(&core, "Error\nGet Data Error\n");
	core_image(core, game, count, argv);
}
