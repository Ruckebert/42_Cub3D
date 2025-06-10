/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:08 by marsenij          #+#    #+#             */
/*   Updated: 2025/05/29 14:18:26 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	destroy_images(t_game *game)
{
	if (game->tex_north.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_north.img);
	if (game->tex_south.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_south.img);
	if (game->tex_east.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_east.img);
	if (game->tex_west.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_west.img);
	if (game->img)
		mlx_destroy_image(game->mlx_ptr, game->img);
}

static void	destroy_window_and_display(t_game *game)
{
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

static void	free_core_data(t_data *core)
{
	if (!core)
		return ;
	if (core->map)
		free_array(core->map);
	if (core->north)
		free(core->north);
	if (core->south)
		free(core->south);
	if (core->east)
		free(core->east);
	if (core->west)
		free(core->west);
}

int	on_destroy(t_game *game)
{
	t_data	*core;

	core = game->core;
	destroy_images(game);
	destroy_window_and_display(game);
	free_core_data(core);
	exit(0);
	return (0);
}
