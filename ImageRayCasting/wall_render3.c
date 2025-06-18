/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aruckenb <aruckenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:10:00 by marsenij          #+#    #+#             */
/*   Updated: 2025/06/11 11:37:34 by aruckenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int compute_texture_x(t_game *game, t_ray *ray, t_dda *dda, t_texture *tex)
{
    double wall_x = get_wall_x(game, ray, dda);
    int tex_x = (int)(wall_x * tex->width);
    
    // Ensure texture coordinates stay within valid range
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex->width) tex_x = tex->width - 1;
    
    return tex_x;
}

int	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	offset;

	offset = y * tex->line_len + x * (tex->bpp / 8);
	return (*(int *)(tex->data + offset));
}

static void	set_wall_params_basic(t_wall_params *p, int start, int end)
{
	int	slice_h;

	slice_h = end - start;
	p->start = start;
	p->end = end;
	p->original_start = start;
	p->wall_height = slice_h;
}

t_wall_params	compute_wall_params(t_game *game, t_raycast_result *res)
{
	t_wall_params	p;
	int				start;
	int				end;

	compute_wall_dimensions(game, res->corrected_dist, &start, &end);
	set_wall_params_basic(&p, start, end);
	p.tex = select_wall_texture(game, &res->ray, &res->dda);
	p.tex_x = compute_texture_x(game, &res->ray, &res->dda, p.tex);
	return (p);
}

void	draw_ceiling(t_game *game, int col, int start)
{
	int	y;

	y = 0;
	while (y < start)
	{
		my_mlx_pixel_put(game, col, y, game->core->top);
		y++;
	}
}
