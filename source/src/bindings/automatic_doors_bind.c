/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatic_doors_bind.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:34:01 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/06 20:11:02 by mtarrih          ###   ########.fr       */
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
		{
			g_map.buffer[door.x * g_map.height + door.y].cell_type = CELL_EMPTY;
			g_map.buffer[door.x * g_map.height + door.y].opacity = 0;
		}
		else if (distance >= max)
		{
			g_map.buffer[door.x * g_map.height + door.y].cell_type = CELL_DOOR;
			g_map.buffer[door.x * g_map.height + door.y].opacity = 1;
		}
		else
		{
			opacity = (distance - min) / (max - min);
			g_map.buffer[door.x * g_map.height + door.y].cell_type = CELL_DOOR;
			g_map.buffer[door.x * g_map.height + door.y].opacity = opacity;
		}
		i++;
	}
}
