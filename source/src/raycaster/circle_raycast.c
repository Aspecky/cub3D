/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 00:00:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/24 19:10:00 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <float.h>
#include <math.h>

t_raycast_result	circle_raycast(t_vector2 origin, t_vector2 direction,
									double distance, double radius)
{
	t_raycast_result	shortest_ray;
	t_raycast_result	ray;
	t_vector2			start;
	double				angle;
	int					i;

	shortest_ray = (t_raycast_result){.hit = false, .distance = DBL_MAX};
	i = 0;
	while (i < 12)
	{
		angle = ((double)i / 12) * M_PI * 2;
		start = (t_vector2){origin.x + cos(angle) * radius,
			origin.y + sin(angle) * radius};
		ray = raycast(start, direction, distance);
		if (ray.hit)
		{
			ray.distance = vector2_mag(vector2_sub(ray.position, origin));
			if (ray.distance < shortest_ray.distance)
				shortest_ray = ray;
		}
		i++;
	}
	return (shortest_ray);
}
