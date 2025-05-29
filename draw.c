/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:15 by marsenij          #+#    #+#             */
/*   Updated: 2025/05/29 14:28:43 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void draw_player_icon(t_game *game, t_pos pos, int size)
{
    fill_tile(game, pos, size, 0xFF0000);
}

void draw_player_direction_arrow(t_game *game, t_pos center)
{
    int arrow_length = game->m_sq_size / 2;
    int arrow_end_x = center.x + (int)(game->dir_x * arrow_length);
    int arrow_end_y = center.y + (int)(game->dir_y * arrow_length);
    draw_line(game, center.x, center.y, arrow_end_x, arrow_end_y, 0x0000FF);
}

void draw_player(t_game *game)
{
    int margin = game->m_sq_size / 4;
    int player_size = game->m_sq_size - (2 * margin);
    
    t_pos center = get_player_screen_pos(game);
    t_pos icon_pos = {center.x - player_size / 2, center.y - player_size / 2};
    
    draw_player_icon(game, icon_pos, player_size);
    draw_player_direction_arrow(game, center);
}
