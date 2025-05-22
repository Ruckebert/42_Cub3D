#include "header.h"

t_ray init_ray_values(double ray_angle)
{
    t_ray ray;

    ray.dir_x = cos(ray_angle);
    ray.dir_y = sin(ray_angle);
    ray.delta_x = fabs(1 / ray.dir_x);
    ray.delta_y = fabs(1 / ray.dir_y);
    return ray;
}

t_dda init_step_and_sidedist(t_ray ray, double px, double py)
{
    t_dda dda;

    dda.map_x = (int)px;
    dda.map_y = (int)py;
    if (ray.dir_x < 0)
    {
        dda.step_x = -1;
        dda.side_x = (px - dda.map_x) * ray.delta_x;
    }
    else
    {
        dda.step_x = 1;
        dda.side_x = (dda.map_x + 1.0 - px) * ray.delta_x;
    }
    if (ray.dir_y < 0)
    {
        dda.step_y = -1;
        dda.side_y = (py - dda.map_y) * ray.delta_y;
    }
    else
    {
        dda.step_y = 1;
        dda.side_y = (dda.map_y + 1.0 - py) * ray.delta_y;
    }
    return dda;
}

static int row_width(char **map, int y)
{
    if (map == NULL || map[y] == NULL)
        return 0;
    return ft_strlen(map[y]);
}

int map_height(char **map)
{
    int h = 0;
    while (map[h])
        h++;
    return h;
}

void perform_dda(t_game *game, t_ray ray, t_dda *dda)
{
    int hit = 0;
    int depth = MAX_DEPTH;
    int H = map_height(game->core->map);
    int W;
    char tile;

    while (!hit && depth--)
    {
        if (dda->side_x < dda->side_y)
        {
            dda->side_x += ray.delta_x;
            dda->map_x += dda->step_x;
            dda->side = 0;
        }
        else
        {
            dda->side_y += ray.delta_y;
            dda->map_y += dda->step_y;
            dda->side = 1;
        }
        if (dda->map_y < 0 || dda->map_y >= H)
            break;
        W = row_width(game->core->map, dda->map_y);
        if (dda->map_x < 0 || dda->map_x >= W)
            break;
        tile = game->core->map[dda->map_y][dda->map_x];
        if (tile == '1' || tile == '2')
            hit = 1;
    }
    if (dda->side == 0)
        dda->perp_dist = dda->side_x - ray.delta_x;
    else
        dda->perp_dist = dda->side_y - ray.delta_y;
}

void get_ray_hit_point(t_game *game, t_ray ray, t_dda dda,
    int *out_x, int *out_y)
{
    double hx;
    double hy;
    int tile;

    hx = game->px + ray.dir_x * dda.perp_dist;
    hy = game->py + ray.dir_y * dda.perp_dist;
    tile = game->m_sq_size;

    *out_x = (int)(hx * tile);
    *out_y = (int)(hy * tile);
}

void cast_ray_dda(t_game *game, double ray_angle)
{
    int px;
    int py;
    int ex;
    int ey;

    t_ray ray = init_ray_values(ray_angle);
    t_dda dda = init_step_and_sidedist(ray, game->px, game->py);
    perform_dda(game, ray, &dda);
    px = (int)(game->px * game->m_sq_size + game->m_sq_size/2);
    py = (int)(game->py * game->m_sq_size + game->m_sq_size/2);
    get_ray_hit_point(game, ray, dda, &ex, &ey);
    draw_line(game, px, py, ex, ey, 0x00FF00);
}

void draw_ceiling_floor(t_game *game, int col, int draw_start, int draw_end, int ceiling_color, int floor_color)
{
    int screen_h;
    int y;

    screen_h = game->win_y;
    y = 0;
    while (y < draw_start)
    {
        my_mlx_pixel_put(game, col, y, ceiling_color);
        y++;
    }
    y = draw_end + 1;
    while (y < screen_h)
    {
        my_mlx_pixel_put(game, col, y, floor_color);
        y++;
    }
}

void draw_walls(t_game *game, int col, int draw_start, int draw_end, char tile_type)
{
    int wall_color;
    int y;

    if (tile_type == '1')
        wall_color = 0x888888;
    else if (tile_type == '2')
        wall_color = 0xAA5500;
    else if (tile_type == '3')
    {
        wall_color = 0x00AA00;
        draw_start = (game->win_y / 2) - (draw_end - draw_start) / 4;
        draw_end = (game->win_y / 2) + (draw_end - draw_start) / 4;
    }
    else
        wall_color = 0x888888;
    y = draw_start;
    while (y <= draw_end)
    {
        my_mlx_pixel_put(game, col, y, wall_color);
        y++;
    }
}

double correct_fisheye(double ray_ang, double player_angle, double perp_dist)
{
    double angle_diff;

    angle_diff = ray_ang - player_angle;
    while (angle_diff > M_PI)
        angle_diff -= 2 * M_PI;
    while (angle_diff < -M_PI)
        angle_diff += 2 * M_PI;
    return (perp_dist * cos(angle_diff));
}

void calculate_wall_height(t_game *game, double perp_dist, int *draw_start, int *draw_end)
{
    double proj_plane_dist;
    int slice_h;

    proj_plane_dist = (game->win_x / 2.0) / tan(FOV / 2.0);
    slice_h = (int)(proj_plane_dist / perp_dist);
    *draw_start = (game->win_y / 2) - (slice_h / 2);
    *draw_end = *draw_start + slice_h;
    if (*draw_start < 0)
        *draw_start = 0;
    if (*draw_end >= game->win_y)
        *draw_end = game->win_y - 1;
}

char get_tile_type(t_game *game, t_dda dda)
{
    char tile_type;

    tile_type = '0';
    if (dda.map_y >= 0 && dda.map_y < map_height(game->core->map) &&
        dda.map_x >= 0 && dda.map_x < (int)ft_strlen(game->core->map[dda.map_y]))
    {
        tile_type = game->core->map[dda.map_y][dda.map_x];
    }
    return tile_type;
}

static void dda_cast(t_game *game, double ray_ang, t_ray *ray, t_dda *dda)
{
    *ray = init_ray_values(ray_ang);
    *dda = init_step_and_sidedist(*ray, game->px, game->py);
    perform_dda(game, *ray, dda);
}

static void compute_slice_dims(t_game *game, t_dda *dda, double ray_ang, int *start, int *end)
{
    double perp;
    double proj;
    int h;

    perp = correct_fisheye(ray_ang, game->angle, dda->perp_dist);
    proj = (game->win_x / 2.0) / tan(FOV / 2.0);
    h = (int)(proj / perp);
    *start = (game->win_y / 2) - (h / 2);
    *end = *start + h;
    if (*start < 0)
        *start = 0;
    if (*end >= game->win_y)
        *end = game->win_y - 1;
}

static t_texture *select_texture(t_game *game, t_ray *ray, t_dda *dda)
{
    if (dda->side == 0)
        return (ray->dir_x > 0) ? &game->tex_east : &game->tex_west;
    return (ray->dir_y > 0) ? &game->tex_south : &game->tex_north;
}

static int compute_tex_x(t_game *game, t_ray *ray, t_dda *dda, t_texture *tex)
{
    double wall_x;
    int tx;

    if (dda->side == 0)
        wall_x = game->py + dda->perp_dist * ray->dir_y;
    else
        wall_x = game->px + dda->perp_dist * ray->dir_x;
    wall_x -= floor(wall_x);
    tx = (int)(wall_x * tex->width);
    if ((dda->side == 0 && ray->dir_x < 0) || (dda->side == 1 && ray->dir_y > 0))
        tx = tex->width - tx - 1;
    return tx;
}

static int get_texture_pixel(t_texture *tex, int x, int y)
{
    int offset;

    offset = y * tex->line_len + x * (tex->bpp / 8);
    return *(int *)(tex->data + offset);
}

static void draw_ceiling(t_game *game, int col, int start)
{
    int y;

    y = 0;
    while (y < start)
    {
        my_mlx_pixel_put(game, col, y, game->core->top);
        y++;
    }
}

static void draw_floor(t_game *game, int col, int end)
{
    int y;

    y = end + 1;
    while (y < game->win_y)
    {
        my_mlx_pixel_put(game, col, y, game->core->bottom);
        y++;
    }
}

static void draw_wall_slice(t_game *game, int col, t_ray *ray, t_dda *dda, int start, int end)
{
    t_texture *tex;
    int tx;
    int y;
    int d;

    tex = select_texture(game, ray, dda);
    tx = compute_tex_x(game, ray, dda, tex);
    y = start;
    while (y <= end)
    {
        d = (y * 256) - (game->win_y * 128) + ((end - start) * 128);
        my_mlx_pixel_put(
            game,
            col,
            y,
            get_texture_pixel(tex, tx, ((d * tex->height) / (end - start)) / 256)
        );
        y++;
    }
}

void process_column(t_game *game, int col, double ray_ang)
{
    t_ray ray;
    t_dda dda;
    int start;
    int end;

    dda_cast(game, ray_ang, &ray, &dda);
    compute_slice_dims(game, &dda, ray_ang, &start, &end);
    draw_ceiling(game, col, start);
    draw_wall_slice(game, col, &ray, &dda, start, end);
    draw_floor(game, col, end);
}


void render_3d_projection(t_game *game)
{
    double start_ang;
    double step;
    double ray_ang;

    start_ang = game->angle - (FOV / 2.0);
    step = FOV / (double)game->win_x;
    for (int col = 0; col < game->win_x; col++)
    {
        ray_ang = start_ang + col * step;
        process_column(game, col, ray_ang);
    }
}
