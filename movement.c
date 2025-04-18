#include "header.h"

int on_destroy(t_game *game)
{
    mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    mlx_destroy_display(game->mlx_ptr);
    free(game->mlx_ptr);
    exit(0);
    return (0);
}

void eval_keycode(int keycode, t_game *game, double *dx, double *dy)
{
    *dx = 0;
    *dy = 0;
    if (keycode == XK_w)
    {
        *dx = game->dir_x;
        *dy = game->dir_y;
    }
    else if (keycode == XK_s)
    {
        *dx = -game->dir_x;
        *dy = -game->dir_y;
    }
    else if (keycode == XK_d)
    {
        *dx = -game->dir_y;
        *dy = game->dir_x;
    }
    else if (keycode == XK_a)
    {
        *dx = game->dir_y;
        *dy = -game->dir_x;
    }
}

void rotate_player(t_game *game, double delta)
{
    game->angle += delta;
    // wrap it to [0, 2π)
    if (game->angle < 0)            game->angle += 2 * M_PI;
    else if (game->angle >= 2*M_PI) game->angle -= 2 * M_PI;

    game->dir_x = cos(game->angle);
    game->dir_y = sin(game->angle);
}

void playermove(int keycode, t_game *game)
{
    double dx = 0, dy = 0;
    double move_speed = 0.1;

    eval_keycode(keycode, game, &dx, &dy);
    game->px += dx * move_speed;
    game->py += dy * move_speed;
}

void render(t_game *game)
{
    draw_minimap(game);
    draw_grid(game);
    draw_player(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->minimap_img, 0, 0);
}

int on_key_press(int keycode, void *param)
{
    t_game *game = (t_game *)param;

    if (keycode == XK_Escape)
        on_destroy(game);

    else if (keycode == XK_Left)
    {
        rotate_player(game, -ROT_SPEED);
        render(game);
    }
    else if (keycode == XK_Right)
    {
        rotate_player(game, +ROT_SPEED);
        render(game);
    }
    else if (keycode == XK_w || keycode == XK_s
          || keycode == XK_a || keycode == XK_d)
    {
        playermove(keycode, game);
        render(game);
    }
    return (0);
}
