#include "header.h"
#include <mlx.h>

int on_destroy(t_game *game)
{
    mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	if (game->core->map)
		free_array(game->core->map);
	if (game->core->map)
		free(game->core->west);
	if (game->core->map)
		free(game->core->east);
	if (game->core->map)
		free(game->core->south);
	if (game->core->map)
		free(game->core->north);
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

void init_dir(t_data *core, t_game *game)
{
	if (core->dir == 'E')
		game->angle = 0.0;
	else if (core->dir == 'S')
		game->angle = M_PI/2;
	else if (core->dir == 'W')
		game->angle = M_PI;
	else if (core->dir == 'N')
		game->angle = 3 * M_PI/2;
	game->dir_x = cos(game->angle);
	game->dir_y = sin(game->angle);
}

int init(t_data *core, t_game *game)
{
    game->core    = core;
    game->mlx_ptr = mlx_init();
    if (!game->mlx_ptr)
        return (1);

    game->px += 0.5;
    game->py += 0.5;
    init_dir(core, game);

    game->m_sq_size = 7;
    game->win_x     = WIDTH;
    game->win_y     = HEIGHT;
    game->win_ptr   = mlx_new_window(
        game->mlx_ptr, game->win_x, game->win_y,
        "so_long_with_extrasteps"
    );
    if (!game->win_ptr)
        return (1);

    game->img      = mlx_new_image(
        game->mlx_ptr, game->win_x, game->win_y
    );
    game->img_data = mlx_get_data_addr(
		game->img, &game->bpp, &game->line_len, &game->endian
    );

    // ——— Load wall textures ———
    int w, h;
    game->tex_north.img = mlx_xpm_file_to_image(
        game->mlx_ptr, core->north, &w, &h
    );
    game->tex_south.img = mlx_xpm_file_to_image(
        game->mlx_ptr, core->south, &w, &h
    );
    game->tex_east.img  = mlx_xpm_file_to_image(
        game->mlx_ptr, core->east,  &w, &h
    );
    game->tex_west.img  = mlx_xpm_file_to_image(
        game->mlx_ptr, core->west,  &w, &h
    );
    game->tex_north.width  = w;
    game->tex_north.height = h;
    game->tex_south.width  = w;
    game->tex_south.height = h;
    game->tex_east.width   = w;
    game->tex_east.height  = h;
    game->tex_west.width   = w;
    game->tex_west.height  = h;

    game->tex_north.data = mlx_get_data_addr(
        game->tex_north.img,
        &game->tex_north.bpp,
        &game->tex_north.line_len,
        &game->tex_north.endian
    );
    game->tex_south.data = mlx_get_data_addr(
        game->tex_south.img,
        &game->tex_south.bpp,
        &game->tex_south.line_len,
        &game->tex_south.endian
    );
    game->tex_east.data = mlx_get_data_addr(
        game->tex_east.img,
        &game->tex_east.bpp,
        &game->tex_east.line_len,
        &game->tex_east.endian
    );
    game->tex_west.data = mlx_get_data_addr(
        game->tex_west.img,
        &game->tex_west.bpp,
        &game->tex_west.line_len,
        &game->tex_west.endian
    );

    int rows = map_height(core->map);
    int cols = 0;
    while (core->map[0][cols])
        cols++;
    game->mini_w     = cols * game->m_sq_size;
    game->mini_h     = rows * game->m_sq_size;
    game->mini_off_x = 0;
    game->mini_off_y = 0;

    return (0);
}
