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
        return 0x000000;
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
            t_pos base = get_minimap_pos(game, j, i);
            fill_tile(game, base, game->m_sq_size, color);
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

void draw_parallel_lines(t_game *game, t_pos start, int count, int spacing, 
                        int length, int is_vertical, int color)
{
    int i = 0;
    while (i <= count)
    {
        int x1, y1, x2, y2;
        if (is_vertical)
        {
            x1 = x2 = start.x + i * spacing;
            y1 = start.y;
            y2 = start.y + length;
        }
        else
        {
            x1 = start.x;
            x2 = start.x + length;
            y1 = y2 = start.y + i * spacing;
        }
        draw_line(game, x1, y1, x2, y2, color);
        i++;
    }
}

void draw_grid_lines(t_game *game, t_pos offset, int cols, int rows, int tile_size)
{
    draw_parallel_lines(game, offset, cols, tile_size, rows * tile_size, 1, 0x222222);
    draw_parallel_lines(game, offset, rows, tile_size, cols * tile_size, 0, 0x222222);
}

void draw_grid(t_game *game)
{
    t_pos offset = {game->mini_off_x, game->mini_off_y};
    int cols = game->mini_w / game->m_sq_size;
    int rows = game->mini_h / game->m_sq_size;
    draw_grid_lines(game, offset, cols, rows, game->m_sq_size);
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

void draw_player_icon(t_game *game, t_pos pos, int size)
{
    fill_tile(game, pos, size, 0xFF0000);
}

t_pos get_player_screen_pos(t_game *game)
{
    t_pos pos;
    pos.x = game->mini_off_x + (int)(game->px * game->m_sq_size);
    pos.y = game->mini_off_y + (int)(game->py * game->m_sq_size);
    return pos;
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

int minimap(t_game *game)
{
    draw_minimap(game);
    draw_grid(game);
    draw_player(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
    return (0);
}