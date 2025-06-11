/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:08 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:39:15 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	init_dir(t_data *core, t_game *game)
{
	if (core->dir == 'E')
		game->angle = 0.0;
	else if (core->dir == 'S')
		game->angle = M_PI / 2;
	else if (core->dir == 'W')
		game->angle = M_PI;
	else if (core->dir == 'N')
		game->angle = 3 * M_PI / 2;
	game->dir_x = cos(game->angle);
	game->dir_y = sin(game->angle);
}

static int	init_window(t_game *game)
{
	game->win_x = WIDTH;
	game->win_y = HEIGHT;
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->win_x,
			game->win_y, "so_long_with_extrasteps");
	if (!game->win_ptr)
		return (1);
	game->img = mlx_new_image(game->mlx_ptr, game->win_x, game->win_y);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_len, &game->endian);
	return (0);
}

static int	load_textures(t_data *core, t_game *game)
{
	int	w;
	int	h;

	game->tex_north.img = mlx_xpm_file_to_image(game->mlx_ptr,
			core->north, &w, &h);
	game->tex_south.img = mlx_xpm_file_to_image(game->mlx_ptr,
			core->south, &w, &h);
	game->tex_east.img = mlx_xpm_file_to_image(game->mlx_ptr,
			core->east, &w, &h);
	game->tex_west.img = mlx_xpm_file_to_image(game->mlx_ptr,
			core->west, &w, &h);
	if (!game->tex_west.img || !game->tex_east.img
		|| !game->tex_south.img || !game->tex_north.img)
		return (1);
	game->tex_north.width = w;
	game->tex_north.height = h;
	game->tex_south.width = w;
	game->tex_south.height = h;
	game->tex_east.width = w;
	game->tex_east.height = h;
	game->tex_west.width = w;
	game->tex_west.height = h;
	return (0);
}

static void	load_texture_data(t_game *game)
{
	game->tex_north.data = mlx_get_data_addr(game->tex_north.img,
			&game->tex_north.bpp, &game->tex_north.line_len,
			&game->tex_north.endian);
	game->tex_south.data = mlx_get_data_addr(game->tex_south.img,
			&game->tex_south.bpp, &game->tex_south.line_len,
			&game->tex_south.endian);
	game->tex_east.data = mlx_get_data_addr(game->tex_east.img,
			&game->tex_east.bpp, &game->tex_east.line_len,
			&game->tex_east.endian);
	game->tex_west.data = mlx_get_data_addr(game->tex_west.img,
			&game->tex_west.bpp, &game->tex_west.line_len,
			&game->tex_west.endian);
}

int	init(t_data *core, t_game *game)
{
	game->core = core;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (1);
	game->px += 0.5;
	game->py += 0.5;
	init_dir(core, game);
	if (init_window(game))
		return (1);
	if (load_textures(core, game))
		return (1);
	load_texture_data(game);
	init_minimap(core, game);
	return (0);
}
