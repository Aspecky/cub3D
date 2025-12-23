/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_marker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:52:51 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/23 19:20:05 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "minimap.h"
#include <mlx_aux/Color4.h>
#include <mlx_aux/mlx_aux.h>

void	draw_player_marker(void)
{
	int			marker_radius;
	t_ivector2	iter;
	int			radius_sq;

	marker_radius = g_minimap.tile_size / 6;
	if (marker_radius < 2)
		marker_radius = 2;
	radius_sq = marker_radius * marker_radius;
	iter.y = -marker_radius;
	while (iter.y <= marker_radius)
	{
		iter.x = -marker_radius;
		while (iter.x <= marker_radius)
		{
			if (iter.x * iter.x + iter.y * iter.y <= radius_sq)
			{
				mlx_put_pixel(g_minimap.img, g_minimap.center.x + iter.x,
					g_minimap.center.y + iter.y,
					color4_from_hex(MINIMAP_COLOR_PLAYER));
			}
			iter.x++;
		}
		iter.y++;
	}
}
