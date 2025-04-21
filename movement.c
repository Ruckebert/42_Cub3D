#include "header.h"
/*
int is_wall(t_game *game, double x, double y)
{
    int map_x = (int)floor(x);
    int map_y = (int)floor(y);
    
    int height = map_height(game->core->Map);
    if (map_y < 0 || map_y >= height)
        return 1;
    
    int width = ft_strlen(game->core->Map[map_y]);
    if (map_x < 0 || map_x >= width)
        return 1;
    
    return (game->core->Map[map_y][map_x] == '1');
}
*/
void rotate_player(t_game *game, double delta)
{
    game->angle += delta;
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
    
    double new_x = game->px + dx * move_speed;
    double new_y = game->py + dy * move_speed;
    
    // Debug print to see what position we're checking
    printf("Checking position: (%f, %f) -> (%f, %f)\n", 
           game->px, game->py, new_x, new_y);
    
    // Check the actual map tile at destination
    int map_x = (int)floor(new_x);
    int map_y = (int)floor(new_y);
    
    if (map_y >= 0 && map_y < map_height(game->core->Map) &&
        game->core->Map[map_y] != NULL && 
        map_x >= 0 && map_x < (int)ft_strlen(game->core->Map[map_y])) {
        
        char tile = game->core->Map[map_y][map_x];
        printf("Tile at destination: '%c'\n", tile);
        
        // If this is a closed door, try to open it
        if (tile == '2') {
            printf("Attempting to open door at (%d, %d)\n", map_x, map_y);
            game->core->Map[map_y][map_x] = '3';
        }
    }
    
    // Allow movement through open doors ('3')
    if (!is_wall(game, new_x, game->py) || 
        (map_y >= 0 && map_y < map_height(game->core->Map) &&
         game->core->Map[map_y] != NULL && map_x >= 0 && 
         map_x < (int)ft_strlen(game->core->Map[map_y]) && 
         game->core->Map[map_y][map_x] == '3'))
    {
        game->px = new_x;
    }
    else
        printf("X movement blocked\n");
        
    if (!is_wall(game, game->px, new_y) || 
        (map_y >= 0 && map_y < map_height(game->core->Map) &&
         game->core->Map[map_y] != NULL && map_x >= 0 && 
         map_x < (int)ft_strlen(game->core->Map[map_y]) && 
         game->core->Map[map_y][map_x] == '3'))
    {
        game->py = new_y;
    }
    else
        printf("Y movement blocked\n");
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

