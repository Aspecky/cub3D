/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:47:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/05 18:33:31 by mtarrih          ###   ########.fr       */
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

	ray.stepSize = (t_vector2){1e30, 1e30};
	if (direction.x != 0)
		ray.stepSize.x = fabs(1 / direction.x);
	if (direction.y != 0)
		ray.stepSize.y = fabs(1 / direction.y);

	t_ivector2 mapPos = {(int)origin.x, (int)origin.y};
	t_ivector2 step = {0, 0};

	if (direction.x < 0)
	{
		step.x = -1;
		ray.sideDist.x = (origin.x - mapPos.x) * ray.stepSize.x;
	} else
	{
		step.x = 1;
		ray.sideDist.x = (mapPos.x + 1.0 - origin.x) * ray.stepSize.x;
	}
	if (direction.y < 0)
	{
		step.y = -1;
		ray.sideDist.y = (origin.y - mapPos.y) * ray.stepSize.y;
	} else
	{
		step.y = 1;
		ray.sideDist.y = (mapPos.y + 1.0 - origin.y) * ray.stepSize.y;
	}

	ray.distance = 0.0;
	while (!ray.hit)
	{
		if (ray.sideDist.x < ray.sideDist.y)
		{
			mapPos.x += step.x;
			ray.distance = ray.sideDist.x;
			ray.sideDist.x += ray.stepSize.x;
			ray.side = 0;
		} else
		{
			mapPos.y += step.y;
			ray.distance = ray.sideDist.y;
			ray.sideDist.y += ray.stepSize.y;
			ray.side = 1;
		}
		if (ray.distance >= distance)
			break;
		if (mapPos.x >= 0 && mapPos.x < g_map.width && mapPos.y >= 0 &&
			mapPos.y < g_map.height &&
			g_map.buffer[mapPos.x * g_map.height + mapPos.y] > 0)
		{
			ray.hit = true;
			ray.position =
				vector2_add(origin, vector2_scale(direction, ray.distance));
			// ray.cell_type =
			// 	ceilf(g_map.buffer[mapPos.x * g_map.height + mapPos.y]);
			// ray.cell_opacity =
			// 	1 - fmodf(g_map.buffer[mapPos.x * g_map.height + mapPos.y], 1);
			double tmp;
			ray.cell_opacity =
				modf(g_map.buffer[mapPos.x * g_map.height + mapPos.y], &tmp);
			ray.cell_type = tmp;
			if (ray.cell_opacity == 0)
				ray.cell_opacity = 1;
		}
	}
	return (ray);
}
