#include "header.h"

void rotate_player(t_game *game, double delta)
{
    game->angle += delta;
    if (game->angle < 0) game->angle += 2 * M_PI;
    else if (game->angle >= 2*M_PI) game->angle -= 2 * M_PI;
    game->dir_x = cos(game->angle);
    game->dir_y = sin(game->angle);
}

void check_and_open_door(t_game *game, double new_x, double new_y)
{
    int map_x;
    int map_y;

    map_x = (int)floor(new_x);
    map_y = (int)floor(new_y);
    if (map_y >= 0 && map_y < map_height(game->core->map) &&
        game->core->map[map_y] != NULL &&
        map_x >= 0 && map_x < (int)ft_strlen(game->core->map[map_y])) {
        char tile = game->core->map[map_y][map_x];
        //printf("Tile at destination: '%c'\n", tile);
        if (tile == '2') {
            printf("Attempting to open door at (%d, %d)\n", map_x, map_y);
            game->core->map[map_y][map_x] = '3';
        }
    }
}

void handle_wall_collision(t_game *game, double new_x, double new_y, double dx, double dy, double wall_buffer)
{
    if (!is_wall(game, new_x + (dx > 0 ? wall_buffer : -wall_buffer), game->py) &&
        !is_wall(game, new_x + (dx > 0 ? wall_buffer : -wall_buffer), game->py + wall_buffer) &&
        !is_wall(game, new_x + (dx > 0 ? wall_buffer : -wall_buffer), game->py - wall_buffer)) {
        game->px = new_x;
    } else {
        printf("X movement blocked\n");
    }
    if (!is_wall(game, game->px, new_y + (dy > 0 ? wall_buffer : -wall_buffer)) &&
        !is_wall(game, game->px + wall_buffer, new_y + (dy > 0 ? wall_buffer : -wall_buffer)) &&
        !is_wall(game, game->px - wall_buffer, new_y + (dy > 0 ? wall_buffer : -wall_buffer))) {
        game->py = new_y;
    } else {
        printf("Y movement blocked\n");
    }
}

void recover_from_wall(t_game *game)
{
    double test_offset;
    double test_angle;
    double test_x;
    double test_y;

    printf("ERROR: Player stuck in wall! Attempting recovery...\n");
    test_offset = 0.1;
    while (test_offset < 1.0)
    {
        int i = 0;
        while (i < 8)
        {
            test_angle = i * M_PI / 4;
            test_x = game->px + cos(test_angle) * test_offset;
            test_y = game->py + sin(test_angle) * test_offset;
            if (!is_wall(game, test_x, test_y)) {
                game->px = test_x;
                game->py = test_y;
                printf("Recovery successful: moved to (%f, %f)\n", test_x, test_y);
                return;
            }
            i++;
        }
        test_offset += 0.1;
    }
}

void playermove(int keycode, t_game *game)
{
    double dx = 0;
    double dy = 0;
    double move_speed = 0.1;
    double wall_buffer = 0.1;
    eval_keycode(keycode, game, &dx, &dy);
    double new_x = game->px + dx * move_speed;
    double new_y = game->py + dy * move_speed;
    //printf("Checking position: (%f, %f) -> (%f, %f)\n",
    //      game->px, game->py, new_x, new_y);
    check_and_open_door(game, new_x, new_y);
    handle_wall_collision(game, new_x, new_y, dx, dy, wall_buffer);
    if (is_wall(game, game->px, game->py)) {
        recover_from_wall(game);
    }
}

void render(t_game *game)
{
    update_doors(game);
    ft_bzero(game->img_data, game->win_x * game->win_y * (game->bpp / 8));
    render_3d_projection(game);
    draw_minimap(game);
    draw_grid(game);
    draw_player(game);
    mlx_put_image_to_window(
        game->mlx_ptr,
        game->win_ptr,
        game->img,
        0, 0
    );
}

int on_key_press(int keycode, void *param)
{
    t_game *game = (t_game *)param;
    if (keycode == XK_Escape)
        on_destroy(game);
    else if (keycode == XK_Left)
        rotate_player(game, -ROT_SPEED);
    else if (keycode == XK_Right)
        rotate_player(game, +ROT_SPEED);
    else if (keycode == XK_w || keycode == XK_s
             || keycode == XK_a || keycode == XK_d)
        playermove(keycode, game);
    return (0);
}