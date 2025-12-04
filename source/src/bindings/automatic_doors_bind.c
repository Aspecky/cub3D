/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automatic_doors_bind.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:34:01 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/04 19:06:58 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
#include "types.h"

void automatic_doors_bind(void *param)
{
	t_vector2 pos;
	t_ivector2 door;
	int	i;

	(void)param;
	pos = g_camera.pos;
	i = 0;
	while (i < g_doors.count)
	{
		door = g_doors.locations[i];
		if (vector2_mag(vector2_sub((t_vector2){door.x + 0.5, door.y + 0.5}, pos)) < 1)
		{
			g_map.buffer[door.x * g_map.height + door.y] = (float)CELL_EMPTY;
		}
		else
			g_map.buffer[door.x * g_map.height + door.y] = (float)CELL_DOOR;
		i++;
	}
}
