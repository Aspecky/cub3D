/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:06:33 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/23 19:22:36 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "minimap.h"
#include <mlx_aux/Color4.h>
#include <mlx_aux/mlx_aux.h>

static void	draw_pixel_if_valid(t_ivector2 pos, t_color_rgb rgb)
{
	t_ivector2	delta;
	uint8_t		*ptr;

	delta = ivector2_sub(pos, g_minimap.center);
	if (pos.x >= 0 && pos.x < (int)g_minimap.img->width && pos.y >= 0
		&& pos.y < (int)g_minimap.img->height && delta.x * delta.x + delta.y
		* delta.y < g_minimap.radius_sq)
	{
		ptr = g_minimap.img->pixels + ((pos.y * g_minimap.img->width + pos.x)
				* 4);
		ptr[0] = rgb.r;
		ptr[1] = rgb.g;
		ptr[2] = rgb.b;
		ptr[3] = rgb.alpha;
	}
}

void	draw_tile(int px_x, int px_y, uint32_t tile_size, uint32_t color)
{
	t_ivector2	iter;
	t_color_rgb	rgb;

	rgb = color4_to_rgb(color);
	iter.y = 0;
	while (iter.y < (int)tile_size)
	{
		iter.x = 0;
		while (iter.x < (int)tile_size)
		{
			draw_pixel_if_valid((t_ivector2){px_x + iter.x, px_y + iter.y},
				rgb);
			iter.x++;
		}
		iter.y++;
	}
}
