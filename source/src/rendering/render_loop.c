/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:33:37 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/25 16:16:40 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "raycast.h"
#include "rendering.h"
#include <stdint.h>

static size_t	collect_rays(t_vector2 raydir, t_raycast_result rays[10],
		double distances[10])
{
	t_vector2	raypos;
	t_vector2	unit_raydir;
	double		raydis;
	double		traveled_distance;
	size_t		rays_count;

	raypos = g_player.pos;
	unit_raydir = vector2_unit(raydir);
	raydis = RENDER_DISTANCE;
	traveled_distance = 0;
	rays_count = 0;
	while (rays_count < 10 && raydis > 0)
	{
		rays[rays_count] = raycast(raypos, raydir, raydis);
		if (!rays[rays_count].hit)
			break ;
		distances[rays_count++] = traveled_distance;
		if (rays[rays_count - 1].tile_opacity >= 1)
			break ;
		raypos = vector2_add(rays[rays_count - 1].position,
				vector2_scale(unit_raydir, 0.001));
		raydis -= rays[rays_count - 1].distance;
		traveled_distance += rays[rays_count - 1].distance;
	}
	return (rays_count);
}

static void	draw_opaque_wall(t_wall_render_params params, uint32_t x)
{
	t_draw_common_params	common;

	common.img_ptr = g_img->pixels + (params.draw_start * g_img->width + x) * 4;
	common.img_stride = g_img->width * 4;
	common.tex_col = params.tex_pixels + params.tex_x * params.tex_height * 4;
	common.y = params.draw_start;
	while (common.y < params.draw_end)
	{
		common.tex_y = (uint32_t)params.tex_pos & params.tex_height_mask;
		params.tex_pos += params.step;
		common.tex_ptr = common.tex_col + common.tex_y * 4;
		common.img_ptr[0] = common.tex_ptr[0];
		common.img_ptr[1] = common.tex_ptr[1];
		common.img_ptr[2] = common.tex_ptr[2];
		common.img_ptr[3] = 255;
		common.img_ptr += common.img_stride;
		common.y++;
	}
}

static void	draw_blended_wall(t_wall_render_params params, uint32_t x,
		double opacity)
{
	t_draw_common_params	common;
	uint32_t				new_alpha;
	uint32_t				inv_alpha;

	new_alpha = (uint32_t)(opacity * 255);
	inv_alpha = 255 - new_alpha;
	common.img_ptr = g_img->pixels + (params.draw_start * g_img->width + x) * 4;
	common.img_stride = g_img->width * 4;
	common.tex_col = params.tex_pixels + params.tex_x * params.tex_height * 4;
	common.y = params.draw_start;
	while (common.y < params.draw_end)
	{
		common.tex_y = (uint32_t)params.tex_pos & params.tex_height_mask;
		params.tex_pos += params.step;
		common.tex_ptr = common.tex_col + common.tex_y * 4;
		common.img_ptr[0] = (common.tex_ptr[0] * new_alpha + common.img_ptr[0]
				* inv_alpha) >> 8;
		common.img_ptr[1] = (common.tex_ptr[1] * new_alpha + common.img_ptr[1]
				* inv_alpha) >> 8;
		common.img_ptr[2] = (common.tex_ptr[2] * new_alpha + common.img_ptr[2]
				* inv_alpha) >> 8;
		common.img_ptr[3] = 255;
		common.img_ptr += common.img_stride;
		common.y++;
	}
}

void	render_loop(void *arg)
{
	t_render_loop_vars	vars;

	(void)arg;
	draw_floor_and_ceiling();
	vars.x = 0;
	while (vars.x < g_img->width)
	{
		vars.raydir = vector2_add(g_player.dir,
				vector2_scale(g_player.cam_plane, 2.0 * vars.x / g_img->width
					- 1));
		vars.rays_count = collect_rays(vars.raydir, vars.rays, vars.distances);
		vars.i = vars.rays_count;
		while (vars.i-- > 0)
		{
			vars.ray = vars.rays[vars.i];
			vars.params = calc_wall_render_params(vars.ray, vars.raydir,
					vars.distances[vars.i], (int)g_img->height);
			if (vars.rays_count == 1)
				draw_opaque_wall(vars.params, vars.x);
			else
				draw_blended_wall(vars.params, vars.x, vars.ray.tile_opacity);
		}
		vars.x++;
	}
}
