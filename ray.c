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
    int H = map_height(game->core->Map);
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
        // dynamic bounds check:
        if (dda->map_y < 0 || dda->map_y >= H)
            break;
        int W = row_width(game->core->Map, dda->map_y);
        if (dda->map_x < 0 || dda->map_x >= W)
            break;
        
        char tile = game->core->Map[dda->map_y][dda->map_x];
        // Important change: Only stop on solid walls ('1') and closed doors ('2')
        if (tile == '1' || tile == '2')
            hit = 1;
        // For open doors ('3'), we don't set hit=1, so the ray continues through
    }
    
    // compute perp_dist exactly as before…
    if (dda->side == 0)
        dda->perp_dist = dda->side_x - ray.delta_x;
    else
        dda->perp_dist = dda->side_y - ray.delta_y;
}


void get_ray_hit_point(t_game *game, t_ray ray, t_dda dda,
    int *out_x, int *out_y)
{
    double hx = game->px + ray.dir_x * dda.perp_dist;
    double hy = game->py + ray.dir_y * dda.perp_dist;

    int tile = game->m_sq_size;
    *out_x = (int)(hx * tile);
    *out_y = (int)(hy * tile);
}

void cast_ray_dda(t_game *game, double ray_angle)
{
    t_ray ray = init_ray_values(ray_angle);
    t_dda dda = init_step_and_sidedist(ray, game->px, game->py);

    perform_dda(game, ray, &dda);

    int px = (int)(game->px * game->m_sq_size + game->m_sq_size/2);
    int py = (int)(game->py * game->m_sq_size + game->m_sq_size/2);

    int ex, ey;
    get_ray_hit_point(game, ray, dda, &ex, &ey);

    draw_line(game, px, py, ex, ey, 0x00FF00);
}

void render_3d_projection(t_game *game)
{
    int screen_w = game->win_x;
    int screen_h = game->win_y;
    /* full‑window projection distance */
    double proj_plane_dist = (screen_w / 2.0) / tan(FOV / 2.0);
    double start_angle = game->angle - (FOV / 2.0);
    double angle_step = FOV / (double)screen_w;
    
    // Get floor and ceiling colors from core data
    int ceiling_color = game->core->Top;
    int floor_color = game->core->Bottom;
    
    // Draw each vertical slice of the screen
    for (int col = 0; col < screen_w; col++)
    {
        double ray_ang = start_angle + col * angle_step;
        t_ray ray = init_ray_values(ray_ang);
        t_dda dda = init_step_and_sidedist(ray, game->px, game->py);
        perform_dda(game, ray, &dda);
        double perp_dist = dda.perp_dist;
        int slice_h = (int)(proj_plane_dist / perp_dist);
        int draw_start = (screen_h / 2) - (slice_h / 2);
        int draw_end = draw_start + slice_h;
        
        if (draw_start < 0) draw_start = 0;
        if (draw_end >= screen_h) draw_end = screen_h - 1;
        
        // Draw ceiling (everything above draw_start)
        for (int y = 0; y < draw_start; y++)
            my_mlx_pixel_put(game, col, y, ceiling_color);
        
        // Determine what kind of wall we hit and choose color
        int wall_color;
        char tile_type = '0';
        
        // Make sure we're not out of bounds
        if (dda.map_y >= 0 && dda.map_y < map_height(game->core->Map) &&
            dda.map_x >= 0 && dda.map_x < (int)ft_strlen(game->core->Map[dda.map_y])) {
            tile_type = game->core->Map[dda.map_y][dda.map_x];
        }
        
        if (tile_type == '1') {
            // Regular wall
            wall_color = 0x888888;  // Gray
        } else if (tile_type == '2') {
            // Closed door
            wall_color = 0xAA5500;  // Brown
        } else if (tile_type == '3') {
            // Open door (should be partially transparent/lower)
            wall_color = 0x00AA00;  // Dark green
            // Make open doors appear shorter
            draw_start = (screen_h / 2) - (slice_h / 4);
            draw_end = (screen_h / 2) + (slice_h / 4);
        } else {
            wall_color = 0x888888;  // Default gray
        }
        
        // Draw walls (from draw_start to draw_end)
        for (int y = draw_start; y <= draw_end; y++)
            my_mlx_pixel_put(game, col, y, wall_color);
        
        // Draw floor (everything below draw_end)
        for (int y = draw_end + 1; y < screen_h; y++)
            my_mlx_pixel_put(game, col, y, floor_color);
    }
}
