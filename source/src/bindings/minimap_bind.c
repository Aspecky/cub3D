/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:47:52 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/09 21:10:50 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
#include "types.h"
#include <math.h>
#include <mlx_aux/Color4.h>
#include <mlx_aux/mlx_aux.h>

static uint32_t get_tile_color(enum e_tile tile_type)
{
	if (tile_type == CELL_WALL)
		return (color4_from_rgb((t_color_rgb){100, 100, 100, 255}));
	else if (tile_type == CELL_DOOR)
		return (color4_from_rgb((t_color_rgb){139, 69, 19, 255}));
	return (color4_from_rgb((t_color_rgb){200, 200, 200, 255}));
}

static void draw_tile(int px_x, int px_y, uint32_t tile_size, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;
	int			draw_x;
	int			draw_y;
	int			dx;
	int			dy;

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
			if (draw_x >= 0 && draw_x < (int)g_minimap.img->width
				&& draw_y >= 0 && draw_y < (int)g_minimap.img->height
				&& dx * dx + dy * dy < g_minimap.radius * g_minimap.radius)
				mlx_put_pixel(g_minimap.img, draw_x, draw_y, color);
			x++;
		}
		y++;
	}
}

static void draw_player_marker(void)
{
	uint32_t	marker_size;
	uint32_t	x;
	uint32_t	y;

	marker_size = g_minimap.tile_size / 3;
	if (marker_size < 2)
		marker_size = 2;
	y = 0;
	while (y < marker_size)
	{
		x = 0;
		while (x < marker_size)
		{
			mlx_put_pixel(g_minimap.img,
				g_minimap.center.x - marker_size / 2 + x,
				g_minimap.center.y - marker_size / 2 + y,
				color4_from_rgb((t_color_rgb){255, 0, 0, 255}));
			x++;
		}
		y++;
	}
}

void minimap_bind(void *param)
{
	t_ivector2	tile_start;
	t_ivector2	map_pos;
	t_ivector2	offset;
	int			y;
	int			x;

	(void)param;
	tile_start = (t_ivector2){
		(int)floor(g_camera.pos.x) - g_minimap.tiles_visible / 2,
		(int)floor(g_camera.pos.y) - g_minimap.tiles_visible / 2};
	offset = (t_ivector2){
		(int)(g_minimap.tile_size * (g_camera.pos.x - floor(g_camera.pos.x))),
		(int)(g_minimap.tile_size * (g_camera.pos.y - floor(g_camera.pos.y)))};
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
				y * g_minimap.tile_size - offset.y,
				g_minimap.tile_size, get_tile_color(tile_type));
			x++;
		}
		y++;
	}
	draw_player_marker();
}
