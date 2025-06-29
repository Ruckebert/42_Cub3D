/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:08 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/18 14:41:45 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	init_dir(t_data *core, t_game *game)
{
	if (core->direction == 'E')
		game->angle = 0.0;
	else if (core->direction == 'S')
		game->angle = M_PI / 2;
	else if (core->direction == 'W')
		game->angle = M_PI;
	else if (core->direction == 'N')
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

static int	load_and_validate_texture(t_game *game, char *path, t_texture *tex)
{
	int	w;
	int	h;

	tex->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &w, &h);
	if (!tex->img)
		return (1);
	if (w != 512 || h != 512)
	{
		mlx_destroy_image(game->mlx_ptr, tex->img);
		tex->img = NULL;
		return (1);
	}
	tex->width = w;
	tex->height = h;
	return (0);
}

static int	load_textures(t_data *core, t_game *game)
{
	if (load_and_validate_texture(game, core->north, &game->tex_north))
		return (1);
	if (load_and_validate_texture(game, core->south, &game->tex_south))
		return (1);
	if (load_and_validate_texture(game, core->east, &game->tex_east))
		return (1);
	if (load_and_validate_texture(game, core->west, &game->tex_west))
		return (1);
	return (0);
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
	{
		ft_putstr_fd("Error\nTexture must be a 512x512 XPM file.\n", 2);
		on_destroy(game);
	}
	load_texture_data(game);
	init_minimap(core, game);
	return (0);
}
