/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:51:50 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/18 12:00:19 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	try_move_x(t_game *game, double new_x, double buffer)
{
	if (can_move_to(game, new_x, game->py, buffer))
		game->px = new_x;
}

void	try_move_y(t_game *game, double new_y, double buffer)
{
	if (can_move_to(game, game->px, new_y, buffer))
		game->py = new_y;
}
