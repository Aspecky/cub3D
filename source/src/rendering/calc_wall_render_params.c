/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_render_params.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 15:41:54 by mtarrih           #+#    #+#             */
/*   Updated: 2026/01/10 22:34:28 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "rendering.h"
#include <math.h>

static mlx_texture_t	*tile_type_to_texture(t_raycast_result ray,
		t_vector2 direction)
{
	if (ray.tile_type == CELL_WALL)
	{
		if (ray.side == 0)
		{
			if (direction.x < 0)
				return (g_theme.ea);
			else
				return (g_theme.we);
		}
		else
		{
			if (direction.y < 0)
				return (g_theme.no);
			else
				return (g_theme.so);
		}
	}
	else if (ray.tile_type == CELL_DOOR)
		return (g_theme.door);
	return (g_theme.no);
}

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

static void	calc_texture_params(t_wall_render_params *params,
		t_texture_calc_args args)
{
	mlx_texture_t	*tex;
	uint32_t		tex_width;
	double			wall_x;

	tex = tile_type_to_texture(args.ray, args.raydir);
	tex_width = tex->width;
	params->tex_height = tex->height;
	params->tex_pixels = tex->pixels;
	if (args.ray.side == 0)
		wall_x = args.ray.position.y;
	else
		wall_x = args.ray.position.x;
	wall_x -= floor(wall_x);
	params->tex_x = (uint32_t)(wall_x * tex_width);
	if (args.ray.side == 0 && args.raydir.x > 0)
		params->tex_x = tex_width - params->tex_x - 1;
	if (args.ray.side == 1 && args.raydir.y < 0)
		params->tex_x = tex_width - params->tex_x - 1;
	params->step = (double)params->tex_height / args.line_height;
	params->tex_pos = (params->draw_start - g_player.pitch - (int)(g_player.z
				/ args.total_dist) - ((double)args.h / 2)
			+ ((double)args.line_height / 2)) * params->step;
}

t_wall_render_params	calc_wall_render_params(t_raycast_result ray,
		t_vector2 raydir, double traveled_dist, int h)
{
	t_wall_render_params	params;
	t_texture_calc_args		inputs;
	double					total_dist;
	int						line_height;

	total_dist = traveled_dist + ray.distance;
	line_height = (int)(h / total_dist * ((double)g_img->width
				/ g_img->height));
	inputs.ray = ray;
	inputs.raydir = raydir;
	inputs.total_dist = total_dist;
	inputs.line_height = line_height;
	inputs.h = h;
	calc_draw_bounds(&params, line_height, h, total_dist);
	calc_texture_params(&params, inputs);
	return (params);
}
