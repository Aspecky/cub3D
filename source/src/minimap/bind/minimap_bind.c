/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:47:52 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/23 19:23:17 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "minimap.h"
#include "types.h"
#include <math.h>
#include <mlx_aux/Color4.h>
#include <mlx_aux/mlx_aux.h>

static void	calculate_minimap_offsets(t_ivector2 *tile_start,
		t_ivector2 *offset)
{
	*tile_start = (t_ivector2){(int)floor(g_player.pos.x)
		- g_minimap.tiles_visible / 2, (int)floor(g_player.pos.y)
		- g_minimap.tiles_visible / 2};
	*offset = (t_ivector2){(int)(g_minimap.tile_size * (g_player.pos.x
				- floor(g_player.pos.x))), (int)(g_minimap.tile_size
			* (g_player.pos.y - floor(g_player.pos.y)))};
}

static enum e_tile	get_tile_type(t_ivector2 tile_start, t_ivector2 pos)
{
	t_ivector2	map_pos;

	map_pos = (t_ivector2){tile_start.x + pos.x, tile_start.y + pos.y};
	if (map_pos.x >= 0 && map_pos.x < g_map.width && map_pos.y >= 0
		&& map_pos.y < g_map.height)
		return (g_map.buffer[map_pos.x * g_map.height + map_pos.y].tile_type);
	return (0);
}

static uint32_t	get_tile_color(enum e_tile tile_type)
{
	if (tile_type == CELL_WALL)
		return (color4_from_hex(MINIMAP_COLOR_WALL));
	else if (tile_type == CELL_DOOR)
		return (color4_from_hex(MINIMAP_COLOR_DOOR));
	return (color4_from_hex(MINIMAP_COLOR_FLOOR));
}

void	minimap_bind(void *param)
{
	t_ivector2	tile_start;
	t_ivector2	offset;
	enum e_tile	tile_type;
	t_ivector2	pos;

	(void)param;
	calculate_minimap_offsets(&tile_start, &offset);
	pos.y = 0;
	while (pos.y < g_minimap.tiles_visible + 1)
	{
		pos.x = 0;
		while (pos.x < g_minimap.tiles_visible + 1)
		{
			tile_type = get_tile_type(tile_start, pos);
			draw_tile(pos.x * g_minimap.tile_size - offset.x, pos.y
				* g_minimap.tile_size - offset.y, g_minimap.tile_size,
				get_tile_color(tile_type));
			pos.x++;
		}
		pos.y++;
	}
	draw_player_marker();
}
