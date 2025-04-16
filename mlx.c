#include "header.h"

void init_dir(t_data *core, t_game *game)
{
    if (core->dir == 'S')
    {
        game->dir_x = 0;
        game->dir_y = 1;
    }
    else if (core->dir == 'E')
    {
        game->dir_x = 1;
        game->dir_y = 0;
    }
    else if (core->dir == 'N')
    {
        game->dir_x = 0;
        game->dir_y = -1;
    }
    else if (core->dir == 'W')
    {
        game->dir_x = -1;
        game->dir_y = 0;
    }
}

int init(t_data *core, t_game *game)
{
    game->core = core;
    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        return (1);
    init_dir(core, game);
    game->m_sq_size = 20;
    game->win_x = WIDTH;
    game->win_y = HEIGHT;
    game->win_ptr = mlx_new_window(game->mlx_ptr,
        game->win_x, game->win_y, "so_long_with_extrasteps");
    if (!game->win_ptr)
        return (1);
    game->minimap_img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
    game->dynamic_img = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
    game->minimap_data = mlx_get_data_addr(game->minimap_img,
                                &game->bpp, &game->line_len, &game->endian);
    game->dynamic_data = mlx_get_data_addr(game->dynamic_img,
                                &game->bpp, &game->line_len, &game->endian);
    return (0);
}
