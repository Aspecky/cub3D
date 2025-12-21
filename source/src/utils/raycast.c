/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:47:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/21 22:32:48 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "utils.h"
#include <math.h>

t_raycast_result raycast(t_vector2 origin, t_vector2 direction, double distance)
{
	t_raycast_result ray;

	ray.hit = false;
	ray.side = 0;

	ray.step_size = (t_vector2){1e30, 1e30};
	if (direction.x != 0)
		ray.step_size.x = fabs(1 / direction.x);
	if (direction.y != 0)
		ray.step_size.y = fabs(1 / direction.y);

	t_ivector2 mapPos = {(int)(origin.x), (int)(origin.y)};
	// t_ivector2 mapPos = {(int)floor(origin.x), (int)floor(origin.y)};
	t_ivector2 step = {0, 0};

	if (direction.x < 0)
	{
		step.x = -1;
		ray.side_dist.x = (origin.x - mapPos.x) * ray.step_size.x;
	} else
	{
		step.x = 1;
		ray.side_dist.x = (mapPos.x + 1.0 - origin.x) * ray.step_size.x;
	}
	if (direction.y < 0)
	{
		step.y = -1;
		ray.side_dist.y = (origin.y - mapPos.y) * ray.step_size.y;
	} else
	{
		step.y = 1;
		ray.side_dist.y = (mapPos.y + 1.0 - origin.y) * ray.step_size.y;
	}

	ray.distance = 0.0;
	while (!ray.hit)
	{
		if (ray.side_dist.x < ray.side_dist.y)
		{
			mapPos.x += step.x;
			ray.distance = ray.side_dist.x;
			ray.side_dist.x += ray.step_size.x;
			ray.side = 0;
		} else
		{
			mapPos.y += step.y;
			ray.distance = ray.side_dist.y;
			ray.side_dist.y += ray.step_size.y;
			ray.side = 1;
		}
		if (ray.distance >= distance)
			break;
		int idx = mapPos.x * g_map.height + mapPos.y;
		if (mapPos.x >= 0 && mapPos.x < g_map.width && mapPos.y >= 0 &&
			mapPos.y < g_map.height &&
			g_map.buffer[idx].tile_type > 0)
		{
			ray.hit = true;
			ray.position =
				vector2_add(origin, vector2_scale(direction, ray.distance));
			ray.tile_type =
				g_map.buffer[idx].tile_type;
			ray.tile_opacity =
				g_map.buffer[idx].opacity;
		}
	}
	return (ray);
}
