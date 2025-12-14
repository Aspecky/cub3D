/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 21:45:00 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/14 17:29:07 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "consts.h"

mlx_texture_t *tile_type_to_texture(t_raycast_result ray, t_vector2 direction)
{
	if (ray.tile_type == CELL_WALL)
	{
		if (ray.side == 0)
		{
			if (direction.x < 0)
				return g_theme.ea;
			else
				return g_theme.we;
		} else
		{
			if (direction.y < 0)
				return g_theme.no;
			else
				return g_theme.so;
		}
	} else if (ray.tile_type == CELL_DOOR)
		return g_theme.door;
	return (g_theme.no);
}
