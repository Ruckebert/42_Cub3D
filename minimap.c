#include "header.h"

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    if (x < 0 || x >= game->win_x || y < 0 || y >= game->win_y)
        return;
    char *dst = game->img_data
        + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_minimap(t_game *game)
{
    int tile = game->m_sq_size;
    int rows = map_height(game->core->Map);

    for (int i = 0; i < rows; i++)
    {
        int cols = ft_strlen(game->core->Map[i]);
        for (int j = 0; j < cols; j++)
        {
            int color = (game->core->Map[i][j] == '1') ? 0xFFFFFF : 0x888888;
            int base_x = game->mini_off_x + j * tile;
            int base_y = game->mini_off_y + i * tile;
            for (int yy = 0; yy < tile; yy++)
                for (int xx = 0; xx < tile; xx++)
                    my_mlx_pixel_put(game,
                                     base_x + xx,
                                     base_y + yy,
                                     color);
        }
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
    for (i = 0; i <= steps; i++)
    {
        my_mlx_pixel_put(game, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}

void draw_grid(t_game *game)
{
    int tile    = game->m_sq_size;
    int off_x   = game->mini_off_x;
    int off_y   = game->mini_off_y;
    int cols    = game->mini_w / tile;   // how many vertical lines
    int rows    = game->mini_h / tile;   // how many horizontal lines

    // vertical grid lines
    for (int i = 0; i <= cols; i++)
    {
        int x = off_x + i * tile;
        draw_line(game,
                  x,             off_y,
                  x,             off_y + rows * tile,
                  0x222222);
    }

    // horizontal grid lines
    for (int j = 0; j <= rows; j++)
    {
        int y = off_y + j * tile;
        draw_line(game,
                  off_x,         y,
                  off_x + cols * tile, y,
                  0x222222);
    }
}


void draw_rays(t_game *game)
{
    double start_angle = game->angle - (FOV / 2);
    double angle_step = FOV / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++)
    {
        double ray_angle = start_angle + i * angle_step;
        cast_ray_dda(game, ray_angle);
    }
}


void draw_player(t_game *game)
{
    int tile = game->m_sq_size;
    int margin = tile / 4;
    int player_size = tile - (2 * margin);
    int x = (int)floor((game->px * tile));
    int y = (int)floor((game->py * tile));
    int i, j;

	for (i = 0; i < player_size; i++)
    {
        for (j = 0; j < player_size; j++)
            my_mlx_pixel_put(game, x + margin + j, y + margin + i, 0xFF0000);
    }
    int cx = x + tile / 2;
    int cy = y + tile / 2;
    int arrow_length = tile / 2;
    int arrow_end_x = cx + (int)(game->dir_x * arrow_length);
    int arrow_end_y = cy + (int)(game->dir_y * arrow_length);

    draw_line(game, cx, cy, arrow_end_x, arrow_end_y, 0x0000FF);
    draw_rays(game);
}

int minimap(t_game *game)
{
    draw_minimap(game);
    draw_grid(game);
    draw_player(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
    return (0);
}
