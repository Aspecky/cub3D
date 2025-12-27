/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamar <kamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:16:05 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/26 22:05:07 by kamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binds.h"
#include "consts.h"
#include "init.h"
#include "loaders.h"
#include "types.h"
#include "parsing.h"
#include <MLX42/MLX42.h>
#include <ftlibc/ft_string.h>
#include <mlx_aux/Color4.h>
#include <mlx_aux/HookService.h>
#include <mlx_aux/mlx_aux.h>
#include <stdlib.h>
#include "rendering.h"
#include <fcntl.h>
#include <unistd.h>

double world_map[][5] = {
	{1, 1, 1, 1, 1}, //
	{1, 0, 0, 0, 1}, //
	{1, 0, 0, 0, 1}, //
	{1, 1, 2, 1, 1}, //
	{1, 0, 0, 0, 1}, //
	{1, 0, 0, 0, 1}, //
	{1, 0, 0, 0, 1}, //
	{1, 1, 1, 1, 1}, //
};
int rows = sizeof(world_map) / sizeof(world_map[0]);
int cols = sizeof(world_map[0]) / sizeof(world_map[0][0]);

mlx_t *g_mlx;
mlx_image_t *g_img;
t_hookservice *g_hookservice;
struct s_minimap g_minimap;
struct s_theme g_theme;
struct s_map g_map;
struct s_view_model g_view_model;
struct s_player g_player;
struct s_doors g_doors;

static mlx_t *open_scaled_window(const char *title)
{
	mlx_t *mlx;
	int32_t width;
	int32_t height;

	mlx = mlx_init(1, 1, title, 0);
	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(mlx, (int32_t)(width * MONITOR_SCALE),
						(int32_t)(height * MONITOR_SCALE));
	mlx_set_window_pos(mlx, width / 2 - mlx->width / 2,
					   height / 2 - mlx->height / 2);
	return (mlx);
}

int main(void)
{

	// parse_file();
	// return 0;

	g_mlx = open_scaled_window("cub3d");
	g_img = mlx_new_image(g_mlx, g_mlx->width, g_mlx->height);
	mlx_image_to_window(g_mlx, g_img, 0, 0);
	g_hookservice = hookservice_init(g_mlx);

	g_map.width = sizeof(world_map[0]) / sizeof(world_map[0][0]);
	g_map.height = sizeof(world_map) / sizeof(world_map[0]);
	g_map.buffer = malloc(sizeof(*g_map.buffer) * g_map.width * g_map.height);
	for (int x = 0; x < g_map.width; x++)
	{
		for (int y = 0; y < g_map.height; y++)
		{
			double cell_value = world_map[g_map.height - 1 - y][x];
			g_map.buffer[x * g_map.height + y].tile_type = (int)cell_value;
			g_map.buffer[x * g_map.height + y].opacity =
				cell_value - (int)cell_value;
			if (g_map.buffer[x * g_map.height + y].opacity == 0)
				g_map.buffer[x * g_map.height + y].opacity = 1;
		}
	}

	g_doors.count = 0;
	for (int i = 0; i < g_map.width * g_map.height; i++)
	{
		if (g_map.buffer[i].tile_type == CELL_DOOR)
			g_doors.count++;
	}
	g_doors.locations = malloc(sizeof(t_ivector2) * g_doors.count);
	g_doors.count = 0;
	for (int x = 0; x < g_map.width; x++)
	{
		for (int y = 0; y < g_map.height; y++)
		{
			if (g_map.buffer[x * g_map.height + y].tile_type == CELL_DOOR)
			{
				g_doors.locations[g_doors.count] = (t_ivector2){x, y};
				g_doors.count++;
			}
		}
	}

	init_textures();
	load_player((t_vector2){2, 1.5}, (t_vector2){0, -1});
	bind_loop(g_hookservice, automatic_doors_bind, NULL, 0);

	bind_key(g_hookservice, close_window_bind, NULL,
			 (keys_t[]){MLX_KEY_ESCAPE, -1});
	bind_loop(g_hookservice, render_loop, &g_player, 0);
	load_minimap();
	bind_loop(g_hookservice, fps_counter_bind, NULL, 0);

	mlx_loop(g_mlx);
	mlx_terminate(g_mlx);
	return (0);
}
