#include "header.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= game->win_x || y < 0 || y >= game->win_y)
        return;
    char *dst = game->img_data
                + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void fill_tile(t_game *game, int base_x, int base_y, int tile, int color)
{
    int yy = 0;
    while (yy < tile)
    {
        int xx = 0;
        while (xx < tile)
        {
            my_mlx_pixel_put(game, base_x + xx, base_y + yy, color);
            xx++;
        }
        yy++;
    }
}

void draw_minimap(t_game *game)
{
    int tile = game->m_sq_size;
    int rows = map_height(game->core->Map);
    int i = 0;
    while (i < rows)
    {
        int cols = ft_strlen(game->core->Map[i]);
        int j = 0;
        while (j < cols)
        {
            int color;
            char map_tile = game->core->Map[i][j];
            if (map_tile == '1')
                color = 0xFFFFFF;
            else if (map_tile == '2')
                color = 0xFF0000;
            else if (map_tile == '3')
                color = 0x00FF00;
            else
                color = 0x888888;
            int base_x = game->mini_off_x + j * tile;
            int base_y = game->mini_off_y + i * tile;
            fill_tile(game, base_x, base_y, tile, color);
            j++;
        }
        i++;
    }
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps;
    float x_inc, y_inc;
    float x = x0;
    float y = y0;
    int i;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    if (steps == 0)
        return;
    x_inc = (float)dx / steps;
    y_inc = (float)dy / steps;
    i = 0;
    while (i <= steps)
    {
        my_mlx_pixel_put(game, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
        i++;
    }
}

void draw_grid_lines(t_game *game, int off_x, int off_y, int cols, int rows, int tile)
{
    int i = 0;
    while (i <= cols)
    {
        int x = off_x + i * tile;
        draw_line(game, x, off_y, x, off_y + rows * tile, 0x222222);
        i++;
    }
    int j = 0;
    while (j <= rows)
    {
        int y = off_y + j * tile;
        draw_line(game, off_x, y, off_x + cols * tile, y, 0x222222);
        j++;
    }
}

void draw_grid(t_game *game)
{
    int tile = game->m_sq_size;
    int off_x = game->mini_off_x;
    int off_y = game->mini_off_y;
    int cols = game->mini_w / tile;
    int rows = game->mini_h / tile;
    draw_grid_lines(game, off_x, off_y, cols, rows, tile);
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

void draw_player_icon(t_game *game, int x, int y, int player_size)
{
    int i = 0;
    while (i < player_size)
    {
        int j = 0;
        while (j < player_size)
        {
            my_mlx_pixel_put(game, x + j, y + i, 0xFF0000);
            j++;
        }
        i++;
    }
}

void draw_player(t_game *game)
{
    int tile = game->m_sq_size;
    int margin = tile / 4;
    int player_size = tile - (2 * margin);
    int x = game->mini_off_x + (int)(game->px * tile) - player_size / 2;
    int y = game->mini_off_y + (int)(game->py * tile) - player_size / 2;
    draw_player_icon(game, x, y, player_size);
    int cx = game->mini_off_x + (int)(game->px * tile);
    int cy = game->mini_off_y + (int)(game->py * tile);
    int arrow_length = tile / 2;
    int arrow_end_x = cx + (int)(game->dir_x * arrow_length);
    int arrow_end_y = cy + (int)(game->dir_y * arrow_length);
    draw_line(game, cx, cy, arrow_end_x, arrow_end_y, 0x0000FF);
}

int minimap(t_game *game)
{
    draw_minimap(game);
    draw_grid(game);
    draw_player(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
    return (0);
}