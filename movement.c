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
    // 1) clear dynamic (3D) buffer to black
    for (int y = 0; y < game->win_y; y++)
        for (int x = 0; x < game->win_x; x++)
            my_mlx_pixel_put_3d(game, x, y, 0x000000);

    // 2) draw the 3D projection into dynamic_img
    render_3d_projection(game);

    // 3) draw your 2D minimap overlay
    draw_minimap(game);
    draw_grid(game);
    draw_player(game);

    // 4) push both images: 3D first, then on top your minimap
    mlx_put_image_to_window(
        game->mlx_ptr, game->win_ptr,
        game->dynamic_img,  0, 0
    );
/*    mlx_put_image_to_window(
        game->mlx_ptr, game->win_ptr,
        game->minimap_img,  0, 0
    );*/
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
