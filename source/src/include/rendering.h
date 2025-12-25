/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:33:52 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/25 16:19:51 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "MLX42/MLX42.h"
# include "mlx_aux/Vector2.h"
# include "raycast.h"
# include <stdint.h>

typedef struct s_wall_render_params
{
	int						draw_start;
	int						draw_end;
	uint32_t				tex_height;
	uint8_t					*tex_pixels;
	uint32_t				tex_x;
	double					step;
	double					tex_pos;
	uint32_t				tex_height_mask;
}							t_wall_render_params;

typedef struct s_draw_common_params
{
	uint8_t					*img_ptr;
	uint32_t				img_stride;
	uint8_t					*tex_col;
	uint32_t				tex_y;
	uint8_t					*tex_ptr;
	int						y;
}							t_draw_common_params;

typedef struct s_render_loop_vars
{
	uint32_t				x;
	t_raycast_result		rays[10];
	double					distances[10];
	t_vector2				raydir;
	size_t					rays_count;
	t_raycast_result		ray;
	size_t					i;
	t_wall_render_params	params;
}							t_render_loop_vars;

void						render_loop(void *arg);

typedef struct s_colors
{
	uint32_t				ceil_color;
	uint32_t				floor_color;
}							t_colors;

void						draw_floor_and_ceiling(void);

typedef struct s_texture_calc_inputs
{
	t_raycast_result		ray;
	t_vector2				raydir;
	double					total_dist;
	int						line_height;
	int						h;
}							t_texture_calc_args;

t_wall_render_params		calc_wall_render_params(t_raycast_result ray,
								t_vector2 raydir, double traveled_dist, int h);

#endif
