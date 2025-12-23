/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:47:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/23 16:59:08 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "raycast.h"
#include <math.h>

static t_vector2	calculate_step_size(t_vector2 direction)
{
	t_vector2	step_size;

	step_size = (t_vector2){1e30, 1e30};
	if (direction.x != 0)
		step_size.x = fabs(1 / direction.x);
	if (direction.y != 0)
		step_size.y = fabs(1 / direction.y);
	return (step_size);
}

static void	calculate_step_and_side_dist(t_dda_init params, t_ivector2 *step,
		t_vector2 *side_dist)
{
	if (params.direction.x < 0)
	{
		step->x = -1;
		side_dist->x = (params.origin.x - params.map_pos.x)
			* params.step_size.x;
	}
	else
	{
		step->x = 1;
		side_dist->x = (params.map_pos.x + 1.0 - params.origin.x)
			* params.step_size.x;
	}
	if (params.direction.y < 0)
	{
		step->y = -1;
		side_dist->y = (params.origin.y - params.map_pos.y)
			* params.step_size.y;
	}
	else
	{
		step->y = 1;
		side_dist->y = (params.map_pos.y + 1.0 - params.origin.y)
			* params.step_size.y;
	}
}

static void	perform_dda_step(t_ivector2 *map_pos, t_ivector2 step,
		t_raycast_result *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		map_pos->x += step.x;
		ray->distance = ray->side_dist.x;
		ray->side_dist.x += ray->step_size.x;
		ray->side = 0;
	}
	else
	{
		map_pos->y += step.y;
		ray->distance = ray->side_dist.y;
		ray->side_dist.y += ray->step_size.y;
		ray->side = 1;
	}
}

static void	on_hit(t_raycast_result *ray, t_vector2 origin, t_vector2 direction,
		int idx)
{
	ray->hit = true;
	ray->position = vector2_add(origin, vector2_scale(direction,
				ray->distance));
	ray->tile_type = g_map.buffer[idx].tile_type;
	ray->tile_opacity = g_map.buffer[idx].opacity;
}

t_raycast_result	raycast(t_vector2 origin, t_vector2 direction,
		double distance)
{
	t_raycast_result	ray;
	t_ivector2			map_pos;
	t_ivector2			step;
	int					idx;

	ray = (t_raycast_result){.step_size = calculate_step_size(direction),
		.hit = false, .distance = 0};
	map_pos = (t_ivector2){(int)floor(origin.x), (int)floor(origin.y)};
	step = (t_ivector2){0, 0};
	calculate_step_and_side_dist((t_dda_init){origin, direction, map_pos,
		ray.step_size}, &step, &ray.side_dist);
	while (!ray.hit)
	{
		perform_dda_step(&map_pos, step, &ray);
		if (ray.distance >= distance)
			break ;
		idx = map_pos.x * g_map.height + map_pos.y;
		if (map_pos.x >= 0 && map_pos.x < g_map.width && map_pos.y >= 0
			&& map_pos.y < g_map.height && g_map.buffer[idx].tile_type > 0)
			on_hit(&ray, origin, direction, idx);
	}
	return (ray);
}
