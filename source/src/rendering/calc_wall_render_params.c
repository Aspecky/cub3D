/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_render_params.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:41:54 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/25 15:48:27 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "utils.h"
#include "consts.h"
#include <math.h>

static void	calc_draw_bounds(t_wall_render_params *params, int line_height,
		int h, double total_dist)
{
	params->draw_start = -(line_height / 2) + (h / 2) + g_player.pitch
		+ (int)(g_player.z / total_dist);
	if (params->draw_start < 0)
		params->draw_start = 0;
	params->draw_end = (line_height / 2) + (h / 2) + g_player.pitch
		+ (int)(g_player.z / total_dist);
	if (params->draw_end >= h)
		params->draw_end = h - 1;
}

t_wall_render_params	calc_wall_render_params(t_raycast_result ray,
		t_vector2 raydir, double traveled_dist, int h)
{
	t_wall_render_params	params;
	double					wall_x;
	double					total_dist;
	int						line_height;
	mlx_texture_t			*tex;
	uint32_t				tex_width;

	total_dist = traveled_dist + ray.distance;
	line_height = (int)(h / total_dist * ((double)g_img->width
				/ g_img->height));
	calc_draw_bounds(&params, line_height, h, total_dist);
	tex = tile_type_to_texture(ray, raydir);
	tex_width = tex->width;
	params.tex = tex;
	if (ray.side == 0)
		wall_x = ray.position.y;
	else
		wall_x = ray.position.x;
	wall_x -= floor(wall_x);
	params.tex_x = (uint32_t)(wall_x * tex_width);
	if (ray.side == 0 && raydir.x > 0)
		params.tex_x = tex_width - params.tex_x - 1;
	if (ray.side == 1 && raydir.y < 0)
		params.tex_x = tex_width - params.tex_x - 1;
	params.step = (double)tex->height / line_height;
	params.tex_pos = (params.draw_start - g_player.pitch - (int)(g_player.z
				/ total_dist) - ((double)h / 2) + ((double)line_height / 2)) * params.step;
	params.tex_height_mask = tex->height - 1;
	return (params);
}
