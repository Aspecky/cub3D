/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:33:40 by mtarrih           #+#    #+#             */
/*   Updated: 2026/01/10 18:50:38 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "init.h"
#include "types.h"
#include <ftlibc/ft_string.h>
#include <stddef.h>
#include <stdlib.h>

static enum e_tile	char_to_tile(char c)
{
	if (c == '1')
		return (CELL_WALL);
	else if (c == 'D')
		return (CELL_DOOR);
	else
		return (CELL_EMPTY);
}

static bool	init_map_buffer(t_parsing parse)
{
	int		x;
	int		y;
	char	cell_char;

	g_map.buffer = malloc(sizeof(*g_map.buffer) * g_map.width * g_map.height);
	if (!g_map.buffer)
		return (false);
	x = 0;
	while (x < g_map.width)
	{
		y = 0;
		while (y < g_map.height)
		{
			cell_char = ' ';
			if (x < (int)ft_strlen(parse.map[g_map.height - 1 - y]))
				cell_char = parse.map[g_map.height - 1 - y][x];
			g_map.buffer[x * g_map.height
				+ y].tile_type = char_to_tile(cell_char);
			g_map.buffer[x * g_map.height + y].opacity = 1.0;
			y++;
		}
		x++;
	}
	return (true);
}

static int	count_doors(void)
{
	int	x;
	int	count;

	count = 0;
	x = 0;
	while (x < g_map.width * g_map.height)
	{
		if (g_map.buffer[x].tile_type == CELL_DOOR)
			count++;
		x++;
	}
	return (count);
}

static bool	init_doors(void)
{
	int	x;
	int	y;

	g_doors.count = count_doors();
	g_doors.locations = malloc(sizeof(t_ivector2) * g_doors.count);
	if (!g_doors.locations)
		return (false);
	g_doors.count = 0;
	x = 0;
	while (x < g_map.width)
	{
		y = 0;
		while (y < g_map.height)
		{
			if (g_map.buffer[x * g_map.height + y].tile_type == CELL_DOOR)
			{
				g_doors.locations[g_doors.count] = (t_ivector2){x, y};
				g_doors.count++;
			}
			y++;
		}
		x++;
	}
	return (true);
}

bool	init_map(t_parsing parse)
{
	g_map.width = parse.map_width;
	g_map.height = parse.map_height;
	if (!init_map_buffer(parse))
		return (false);
	if (!init_doors())
		return (false);
	return (true);
}
