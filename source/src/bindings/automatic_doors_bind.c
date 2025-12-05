/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatic_doors_bind.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:34:01 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/05 22:36:54 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
#include "types.h"
#include <stdio.h>

static double min = 1;
static double max = 2;

void automatic_doors_bind(void *param)
{
	t_vector2 pos;
	t_ivector2 door;
	double distance;
	double opacity;
	int i;

	(void)param;
	pos = g_camera.pos;
	i = 0;
	while (i < g_doors.count)
	{
		door = g_doors.locations[i];
		distance = vector2_mag(
			vector2_sub((t_vector2){door.x + 0.5, door.y + 0.5}, pos));
		if (distance <= min)
			g_map.buffer[door.x * g_map.height + door.y] = CELL_EMPTY;
		else if (distance >= max)
			g_map.buffer[door.x * g_map.height + door.y] = CELL_DOOR;
		else
		{
			opacity = (distance - min) / (max - min);
			g_map.buffer[door.x * g_map.height + door.y] =
				(double)CELL_DOOR + opacity;
		}
		i++;
	}
}
