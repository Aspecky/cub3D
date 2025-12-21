/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatic_doors_bind.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:34:01 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/21 22:24:55 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binds.h"
#include "consts.h"
#include "types.h"

static void	set_door_state(t_ivector2 door, enum e_tile tile_type,
		double opacity)
{
	g_map.buffer[door.x * g_map.height + door.y].tile_type = tile_type;
	g_map.buffer[door.x * g_map.height + door.y].opacity = opacity;
}

void	automatic_doors_bind(void *param)
{
	t_vector2	pos;
	t_ivector2	door;
	double		distance;
	int			i;

	(void)param;
	pos = g_player.pos;
	i = 0;
	while (i < g_doors.count)
	{
		door = g_doors.locations[i];
		distance = vector2_mag(vector2_sub((t_vector2){door.x + 0.5, door.y
					+ 0.5}, pos));
		if (distance <= DOOR_FADEOUT_DISTANCE)
			set_door_state(door, CELL_EMPTY, 0);
		else if (distance >= DOOR_FADEIN_DISTANCE)
			set_door_state(door, CELL_DOOR, 1);
		else
			set_door_state(door, CELL_DOOR, (distance - DOOR_FADEOUT_DISTANCE)
				/ (DOOR_FADEIN_DISTANCE - DOOR_FADEOUT_DISTANCE));
		i++;
	}
}
