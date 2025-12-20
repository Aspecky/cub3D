/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:47:52 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 17:41:17 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "consts.h"
#include "types.h"
#include <math.h>
#include <mlx_aux/Color4.h>
#include <mlx_aux/mlx_aux.h>

static uint32_t get_tile_color(enum e_tile tile_type)
{
	if (tile_type == CELL_WALL)
		return (color4_from_hex(MINIMAP_COLOR_WALL));
	else if (tile_type == CELL_DOOR)
		return (color4_from_hex(MINIMAP_COLOR_DOOR));
	return (color4_from_hex(MINIMAP_COLOR_FLOOR));
}

static void draw_tile(int px_x, int px_y, uint32_t tile_size, uint32_t color)
{
	uint32_t x;
	uint32_t y;
	int draw_x;
	int draw_y;
	int dx;
	int dy;
	int radius_sq;
	uint32_t img_width;
	uint32_t img_height;
	uint8_t *pixels;
	uint8_t r, g, b, a;

	img_width = g_minimap.img->width;
	img_height = g_minimap.img->height;
	pixels = g_minimap.img->pixels;
	radius_sq = g_minimap.radius * g_minimap.radius;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	y = 0;
	while (y < tile_size)
	{
		x = 0;
		while (x < tile_size)
		{
			draw_x = px_x + (int)x;
			draw_y = px_y + (int)y;
			dx = draw_x - g_minimap.center.x;
			dy = draw_y - g_minimap.center.y;
			if (draw_x >= 0 && draw_x < (int)img_width && draw_y >= 0 &&
				draw_y < (int)img_height && dx * dx + dy * dy < radius_sq)
			{
				uint8_t *ptr = pixels + ((draw_y * img_width + draw_x) * 4);
				ptr[0] = r;
				ptr[1] = g;
				ptr[2] = b;
				ptr[3] = a;
			}
			x++;
		}
		y++;
	}
}

static void draw_player_marker(void)
{
	int marker_radius;
	int x;
	int y;
	int dx;
	int dy;
	int radius_sq;

	marker_radius = g_minimap.tile_size / 6;
	if (marker_radius < 2)
		marker_radius = 2;
	radius_sq = marker_radius * marker_radius;
	y = -marker_radius;
	while (y <= marker_radius)
	{
		x = -marker_radius;
		while (x <= marker_radius)
		{
			dx = x;
			dy = y;
			if (dx * dx + dy * dy <= radius_sq)
			{
				mlx_put_pixel(g_minimap.img, g_minimap.center.x + x,
							  g_minimap.center.y + y,
							  color4_from_hex(MINIMAP_COLOR_PLAYER));
			}
			x++;
		}
		y++;
	}
}

void minimap_bind(void *param)
{
	t_ivector2 tile_start;
	t_ivector2 map_pos;
	t_ivector2 offset;
	int y;
	int x;

	(void)param;
	tile_start =
		(t_ivector2){(int)floor(g_player.pos.x) - g_minimap.tiles_visible / 2,
					 (int)floor(g_player.pos.y) - g_minimap.tiles_visible / 2};
	offset = (t_ivector2){
		(int)(g_minimap.tile_size * (g_player.pos.x - floor(g_player.pos.x))),
		(int)(g_minimap.tile_size * (g_player.pos.y - floor(g_player.pos.y)))};
	y = 0;
	while (y < g_minimap.tiles_visible + 1)
	{
		x = 0;
		while (x < g_minimap.tiles_visible + 1)
		{
			enum e_tile tile_type;

			tile_type = 0;
			map_pos = (t_ivector2){tile_start.x + x, tile_start.y + y};
			if (map_pos.x >= 0 && map_pos.x < g_map.width && map_pos.y >= 0 &&
				map_pos.y < g_map.height)
				tile_type = g_map.buffer[map_pos.x * g_map.height + map_pos.y]
								.tile_type;
			draw_tile(x * g_minimap.tile_size - offset.x,
					  y * g_minimap.tile_size - offset.y, g_minimap.tile_size,
					  get_tile_color(tile_type));
			x++;
		}
		y++;
	}
	draw_player_marker();
}
