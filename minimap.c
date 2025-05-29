/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:15 by marsenij          #+#    #+#             */
/*   Updated: 2025/05/29 14:31:24 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= game->win_x || y < 0 || y >= game->win_y)
        return;
    char *dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void fill_tile(t_game *game, t_pos base, int tile_size, int color)
{
    int y = 0;
    while (y < tile_size)
    {
        int x = 0;
        while (x < tile_size)
        {
            my_mlx_pixel_put(game, base.x + x, base.y + y, color);
            x++;
        }
        y++;
    }
}

int get_tile_color(char map_tile)
{
    if (map_tile == '1')
        return 0xFFFFFF;
    else if (map_tile == '2')
        return 0xFF0000;
    else if (map_tile == '3')
        return 0x00FF00;
    else if (map_tile == '\n')
        return 0x00000000;
    else
        return 0x888888;
}

t_pos get_minimap_pos(t_game *game, int grid_x, int grid_y)
{
    t_pos pos;
    pos.x = game->mini_off_x + grid_x * game->m_sq_size;
    pos.y = game->mini_off_y + grid_y * game->m_sq_size;
    return pos;
}

void draw_minimap(t_game *game)
{
    int rows = map_height(game->core->map);
    int i = 0;
    
    while (i < rows)
    {
        int cols = ft_strlen(game->core->map[i]);
        int j = 0;
        while (j < cols)
        {
            char map_tile = game->core->map[i][j];
            int color = get_tile_color(map_tile);
            if (color != 0x00000000)
            {
                t_pos base = get_minimap_pos(game, j, i);
                fill_tile(game, base, game->m_sq_size, color);
            }
            j++;
        }
        i++;
    }
}

void init_line(t_line *line, int x0, int y0, int x1, int y1)
{
    line->dx = x1 - x0;
    line->dy = y1 - y0;
    line->steps = abs(line->dx) > abs(line->dy) ? abs(line->dx) : abs(line->dy);
    line->x = x0;
    line->y = y0;
    
    if (line->steps == 0)
    {
        line->x_inc = 0;
        line->y_inc = 0;
    }
    else
    {
        line->x_inc = (float)line->dx / line->steps;
        line->y_inc = (float)line->dy / line->steps;
    }
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    t_line line;
    init_line(&line, x0, y0, x1, y1);
    
    if (line.steps == 0)
        return;
        
    int i = 0;
    while (i <= line.steps)
    {
        my_mlx_pixel_put(game, (int)line.x, (int)line.y, color);
        line.x += line.x_inc;
        line.y += line.y_inc;
        i++;
    }
}

int tile_exists(t_game *game, int row, int col)
{
    int rows = map_height(game->core->map);
    
    if (row < 0 || row >= rows)
        return 0;
    
    int cols = ft_strlen(game->core->map[row]);
    if (col < 0 || col >= cols)
        return 0;
        
    char tile = game->core->map[row][col];
    return (tile != '\n' && tile != '\0');
}

void draw_rays(t_game *game)
{
    double start_angle = game->angle - (FOV / 2);
    double angle_step = FOV / NUM_RAYS;
    int i = 0;
    while (i < NUM_RAYS)
    {
        double ray_angle = start_angle + i * angle_step;
        cast_ray_dda(game, ray_angle);
        i++;
    }
}

t_pos get_player_screen_pos(t_game *game)
{
    t_pos pos;
    pos.x = game->mini_off_x + (int)(game->px * game->m_sq_size);
    pos.y = game->mini_off_y + (int)(game->py * game->m_sq_size);
    return pos;
}

int minimap(t_game *game)
{
    draw_minimap(game);
    draw_grid(game);
    draw_player(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
    return (0);
}