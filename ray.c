/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:52:35 by marsenij          #+#    #+#             */
/*   Updated: 2025/05/29 13:52:36 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int get_map_dimensions(char **map, int y, int *height)
{
	if (y == 0)
	{
		*height = 0;
		while (map[*height])
			(*height)++;
	}
	if (map == NULL || map[y] == NULL)
		return 0;
	return ft_strlen(map[y]);
}

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

void perform_dda(t_game *game, t_ray ray, t_dda *dda)
{
	int hit = 0;
	int depth = MAX_DEPTH;
	int map_height = 0;
	char tile;

	get_map_dimensions(game->core->map, 0, &map_height);
	
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
		
		if (!is_valid_map_pos(game->core->map, dda->map_x, dda->map_y))
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

static double correct_fisheye(double ray_angle, double player_angle, double perp_dist)
{
	double angle_diff = ray_angle - player_angle;
	
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	return (perp_dist * cos(angle_diff));
}

static void compute_wall_dimensions(t_game *game, double corrected_dist, int *start, int *end, int *original_start, int *wall_height)
{
	double proj_plane_dist = (game->win_x / 2.0) / tan(FOV / 2.0);
	int slice_height = (int)(proj_plane_dist / corrected_dist);
	
	*original_start = (game->win_y / 2) - (slice_height / 2);
	*wall_height = slice_height;
	
	*start = *original_start;
	*end = *start + slice_height;
	
	if (*start < 0)
		*start = 0;
	if (*end >= game->win_y)
		*end = game->win_y - 1;
}

static t_texture *select_wall_texture(t_game *game, t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
		return (ray->dir_x > 0) ? &game->tex_east : &game->tex_west;
	return (ray->dir_y > 0) ? &game->tex_south : &game->tex_north;
}

static int compute_texture_x(t_game *game, t_ray *ray, t_dda *dda, t_texture *tex)
{
	double wall_x;
	int tex_x;

	if (dda->side == 0)
		wall_x = game->py + dda->perp_dist * ray->dir_y;
	else
		wall_x = game->px + dda->perp_dist * ray->dir_x;
		
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	
	if ((dda->side == 0 && ray->dir_x < 0) || (dda->side == 1 && ray->dir_y > 0))
		tex_x = tex->width - tex_x - 1;
		
	return tex_x;
}

static int get_texture_pixel(t_texture *tex, int x, int y)
{
	int offset = y * tex->line_len + x * (tex->bpp / 8);
	return *(int *)(tex->data + offset);
}

static t_wall_params compute_wall_params(t_game *game, t_raycast_result *result)
{
	t_wall_params params;

	compute_wall_dimensions(game, result->corrected_dist, &params.start, &params.end, 
						   &params.original_start, &params.wall_height);
	params.tex = select_wall_texture(game, &result->ray, &result->dda);
	params.tex_x = compute_texture_x(game, &result->ray, &result->dda, params.tex);
	
	return params;
}

static void draw_ceiling(t_game *game, int col, int start)
{
	int y = 0;
	while (y < start)
	{
		my_mlx_pixel_put(game, col, y, game->core->top);
		y++;
	}
}

static void draw_floor(t_game *game, int col, int end)
{
	int y = end + 1;
	while (y < game->win_y)
	{
		my_mlx_pixel_put(game, col, y, game->core->bottom);
		y++;
	}
}

static void draw_textured_wall(t_game *game, int col, t_wall_params *params)
{
	int y = params->start;
	
	while (y <= params->end)
	{
		int y_offset_in_full_wall = y - params->original_start;
		int tex_y = (y_offset_in_full_wall * params->tex->height) / params->wall_height;
		
		if (tex_y < 0) 
			tex_y = 0;
		if (tex_y >= params->tex->height) 
			tex_y = params->tex->height - 1;
		
		my_mlx_pixel_put(game, col, y, 
			get_texture_pixel(params->tex, params->tex_x, tex_y));
		y++;
	}
}

static t_raycast_result cast_single_ray(t_game *game, double ray_angle)
{
	t_raycast_result result;
	int map_height = 0;
	
	result.ray = init_ray_values(ray_angle);
	result.dda = init_step_and_sidedist(result.ray, game->px, game->py);
	perform_dda(game, result.ray, &result.dda);
	
	get_map_dimensions(game->core->map, 0, &map_height);
	result.tile_type = get_tile_at_pos(game->core->map, result.dda.map_x, 
		result.dda.map_y);
	result.corrected_dist = correct_fisheye(ray_angle, game->angle, result.dda.perp_dist);
	
	return result;
}

void process_column(t_game *game, int col, double ray_angle)
{
	t_raycast_result result = cast_single_ray(game, ray_angle);
	t_wall_params params = compute_wall_params(game, &result);
	
	draw_ceiling(game, col, params.start);
	draw_textured_wall(game, col, &params);
	draw_floor(game, col, params.end);
}

void render_3d_projection(t_game *game)
{
	double start_angle = game->angle - (FOV / 2.0);
	double angle_step = FOV / (double)game->win_x;
	
	for (int col = 0; col < game->win_x; col++)
	{
		double ray_angle = start_angle + col * angle_step;
		process_column(game, col, ray_angle);
	}
}

void cast_ray_dda(t_game *game, double ray_angle)
{
	t_raycast_result result = cast_single_ray(game, ray_angle);
	
	int px = (int)(game->px * game->m_sq_size + game->m_sq_size/2);
	int py = (int)(game->py * game->m_sq_size + game->m_sq_size/2);
	
	double hit_x = game->px + result.ray.dir_x * result.dda.perp_dist;
	double hit_y = game->py + result.ray.dir_y * result.dda.perp_dist;
	
	int ex = (int)(hit_x * game->m_sq_size);
	int ey = (int)(hit_y * game->m_sq_size);
	
	draw_line(game, px, py, ex, ey, 0x00FF00);
}