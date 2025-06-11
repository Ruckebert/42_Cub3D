/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:51:50 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:42:02 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	recover_from_wall(t_game *game)
{
	double	offset;
	int		i;
	double	angle;
	double	test_x;
	double	test_y;

	offset = 0.1;
	while (offset < 1.0)
	{
		i = 0;
		while (i < 8)
		{
			angle = i * M_PI / 4;
			test_x = game->px + cos(angle) * offset;
			test_y = game->py + sin(angle) * offset;
			if (!is_wall(game, test_x, test_y))
			{
				game->px = test_x;
				game->py = test_y;
				return ;
			}
			i++;
		}
		offset += 0.1;
	}
}

void	playermove(int keycode, t_game *game)
{
	double	dx;
	double	dy;
	double	new_x;
	double	new_y;
	double	move_speed;

	dx = 0;
	dy = 0;
	move_speed = 0.1;
	eval_keycode(keycode, game, &dx, &dy);
	new_x = game->px + dx * move_speed;
	new_y = game->py + dy * move_speed;
	try_open_door(game, new_x, new_y);
	try_move_x(game, new_x, 0.1);
	try_move_y(game, new_y, 0.1);
	if (is_wall(game, game->px, game->py))
		recover_from_wall(game);
}

void	render(t_game *game)
{
	update_doors(game);
	ft_bzero(game->img_data, game->win_x * game->win_y * (game->bpp / 8));
	render_3d_projection(game);
	draw_minimap(game);
	draw_grid(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
}

int	on_key_press(int keycode, void *param)
{
	t_game	*game;
	double	rot_speed;

	game = (t_game *)param;
	rot_speed = M_PI / 16;
	if (keycode == XK_Escape)
		on_destroy(game);
	else if (keycode == XK_Left)
		rotate_player(game, -rot_speed);
	else if (keycode == XK_Right)
		rotate_player(game, rot_speed);
	else if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
		playermove(keycode, game);
	return (0);
}
