/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:16:05 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/13 17:21:15 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
#include "loaders.h"
#include "types.h"
#include "utils.h"
#include <MLX42/MLX42.h>
#include <ftlibc/ft_string.h>
#include <math.h>
#include <mlx_aux/Color4.h>
#include <mlx_aux/HookService.h>
#include <mlx_aux/mlx_aux.h>
#include <stdio.h>
#include <stdlib.h>

// int world_map[][23] = {
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
// 	{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
// 	{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
// 	{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
// 	{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
// 	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
// 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

// double world_map[][7] = {
// 	{1, 1, 1, 1, 1, 1, 1}, //
// 	{1, 1, 0, 0, 0, 0, 1}, //
// 	{1, 1, 0, 0, 0, 0, 1}, //
// 	{1, 1, 0, 0, 0, 0, 1}, //
// 	{1, 1, 2, 1, 1, 0, 1}, //
// 	{1, 0, 0, 0, 1, 2, 1}, //
// 	// {1, 0, 1, 0, 0, 0, 1}, //
// 	{1.1, 1.2, 1.3, 1.4, 1.5, 0, 1}, //
// 	{1, 1, 1, 1, 1, 1, 1},			 //
// };
double world_map[][5] = {
	{1, 1, 1, 1, 1}, //
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
// struct s_minimap g_minimap;
struct s_theme g_theme;
struct s_map g_map;
struct s_view_model g_view_model;
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

static void draw_floor_and_ceiling(void)
{
	uint32_t i;
	uint32_t ceil_end;
	uint32_t total_size;
	uint32_t *pixels;
	uint32_t ceil_color;
	uint32_t floor_color;

	pixels = (uint32_t *)g_img->pixels;
	ceil_end = g_img->width * (g_img->height / 2 + g_camera.pitch);
	total_size = g_img->width * g_img->height;

	ceil_color = ((g_theme.ceiling >> 24) & 0xFF) |
				 ((g_theme.ceiling >> 8) & 0xFF00) |
				 ((g_theme.ceiling << 8) & 0xFF0000) | 0xFF000000;
	floor_color = ((g_theme.floor >> 24) & 0xFF) |
				  ((g_theme.floor >> 8) & 0xFF00) |
				  ((g_theme.floor << 8) & 0xFF0000) | 0xFF000000;

	// Ceiling (first half)
	i = 0;
	while (i < ceil_end && i < total_size)
		pixels[i++] = ceil_color;
	// Floor (second half)
	while (i < total_size)
		pixels[i++] = floor_color;
}

static mlx_texture_t *tile_type_to_texture(t_raycast_result ray,
										   t_vector2 direction)
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

static void main_loop(void *arg)
{
	uint32_t x;
	uint32_t img_width;
	uint32_t img_height;
	uint8_t *img_pixels;

	(void)arg;
	x = 0;
	img_width = g_img->width;
	img_height = g_img->height;
	img_pixels = g_img->pixels;

	draw_floor_and_ceiling();

	while (x < img_width)
	{
		double camX = 2.0 * x / img_width - 1;

		t_raycast_result rays[10];
		double distances[10];

		t_vector2 raypos = g_camera.pos;
		t_vector2 raydir =
			vector2_add(g_camera.dir, vector2_scale(g_camera.plane, camX));
		t_vector2 unit_raydir = vector2_unit(raydir);
		double raydis = 100;

		t_raycast_result ray;
		double traveled_distance = 0;
		size_t rays_count = 0;

		while (rays_count < sizeof(rays) / sizeof(rays[0]) && raydis > 0)
		{
			ray = raycast(raypos, raydir, raydis);
			if (!ray.hit)
				break;
			rays[rays_count] = ray;
			distances[rays_count] = traveled_distance;
			rays_count++;
			if (ray.tile_opacity >= 1)
				break;

			raypos =
				vector2_add(ray.position, vector2_scale(unit_raydir, 0.001));
			raydis -= ray.distance;
			traveled_distance += ray.distance;
		}

		int h = (int)img_height;
		int h_half = h / 2;
		size_t i = rays_count;
		while (i-- > 0)
		{
			ray = rays[i];

			double total_dist = distances[i] + ray.distance;
			int lineHeight = (int)(h / total_dist * ((double)img_width / img_height));
			int lineHeight_half = lineHeight / 2;

			int drawStart = -lineHeight_half + h_half + g_camera.pitch;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight_half + h_half + g_camera.pitch;
			if (drawEnd >= h)
				drawEnd = h - 1;

			mlx_texture_t *tex = tile_type_to_texture(ray, raydir);
			uint32_t tex_width = tex->width;
			uint32_t tex_height = tex->height;
			uint8_t *tex_pixels = tex->pixels;

			double wall_x;
			if (ray.side == 0)
				wall_x = ray.position.y;
			else
				wall_x = ray.position.x;
			wall_x -= floor(wall_x);

			uint32_t tex_x = (uint32_t)(wall_x * tex_width);
			if (ray.side == 0 && raydir.x > 0)
				tex_x = tex_width - tex_x - 1;
			if (ray.side == 1 && raydir.y < 0)
				tex_x = tex_width - tex_x - 1;

			double step = (double)tex_height / lineHeight;
			double texPos = (drawStart - g_camera.pitch - h_half + lineHeight_half) * step;
			uint32_t tex_height_mask = tex_height - 1;

			if (rays_count == 1)
			{
				uint8_t *img_ptr = img_pixels + (drawStart * img_width + x) * 4;
				uint32_t img_stride = img_width * 4;
				uint8_t *tex_col = tex_pixels + tex_x * tex_height * 4;

				for (int y = drawStart; y < drawEnd; y++)
				{
					uint32_t tex_y = (uint32_t)texPos & tex_height_mask;
					texPos += step;

					uint8_t *tex_ptr = tex_col + tex_y * 4;

					img_ptr[0] = tex_ptr[0];
					img_ptr[1] = tex_ptr[1];
					img_ptr[2] = tex_ptr[2];
					img_ptr[3] = 255;

					img_ptr += img_stride;
				}
			} else
			{
				uint32_t new_alpha = (uint32_t)(ray.tile_opacity * 256);
				uint32_t inv_alpha = 256 - new_alpha;
				uint8_t *img_ptr = img_pixels + (drawStart * img_width + x) * 4;
				uint32_t img_stride = img_width * 4;
				uint8_t *tex_col = tex_pixels + tex_x * tex_height * 4;

				for (int y = drawStart; y < drawEnd; y++)
				{
					uint32_t tex_y = (uint32_t)texPos & tex_height_mask;
					texPos += step;

					uint8_t *tex_ptr = tex_col + tex_y * 4;

					img_ptr[0] =
						(tex_ptr[0] * new_alpha + img_ptr[0] * inv_alpha) >> 8;
					img_ptr[1] =
						(tex_ptr[1] * new_alpha + img_ptr[1] * inv_alpha) >> 8;
					img_ptr[2] =
						(tex_ptr[2] * new_alpha + img_ptr[2] * inv_alpha) >> 8;
					img_ptr[3] = 255;

					img_ptr += img_stride;
				}
			}
		}

		x++;
	}
}

static void load_view_model(void)
{
	mlx_texture_t *tex = mlx_load_png("assets/view_model.png");
	mlx_image_t *img = mlx_texture_to_image(g_mlx, tex);
	double ratio = (double)img->height / img->width;
	double width = (double)g_img->width * VIEW_MODEL_SCALE;
	mlx_resize_image(img, width, width * ratio);
	int id =
		mlx_image_to_window(g_mlx, img, g_img->width / 2 - (img->width * 0.4),
							g_img->height - img->height + VIEW_MODEL_DEPTH);
	g_view_model.inst = img->instances + id;
	g_view_model.og_pos =
		(t_ivector2){g_view_model.inst->x, g_view_model.inst->y};
}

int main(void)
{
	g_mlx = open_scaled_window("cub3d");
	g_img = mlx_new_image(g_mlx, g_mlx->width, g_mlx->height);
	mlx_image_to_window(g_mlx, g_img, 0, 0);
	g_hookservice = hookservice_init(g_mlx);

	load_camera((t_vector2){2, 1.5}, (t_vector2){-1, 0});
	load_view_model();

	g_theme.ceiling = color4_from_hex("87CEEB");
	g_theme.floor = color4_from_hex("9B7653");
	g_theme.no = mlx_load_png("assets/North.png");
	g_theme.ea = mlx_load_png("assets/East.png");
	g_theme.so = mlx_load_png("assets/South.png");
	g_theme.we = mlx_load_png("assets/West.png");
	g_theme.door = mlx_load_png("assets/door.png");
	mlx_resize_texture(g_mlx, g_theme.no, 64, 64);
	mlx_resize_texture(g_mlx, g_theme.ea, 64, 64);
	mlx_resize_texture(g_mlx, g_theme.so, 64, 64);
	mlx_resize_texture(g_mlx, g_theme.we, 64, 64);
	transpose_texture(g_theme.no);
	transpose_texture(g_theme.ea);
	transpose_texture(g_theme.so);
	transpose_texture(g_theme.we);
	transpose_texture(g_theme.door);

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

	bind_key(g_hookservice, close_window_bind, NULL,
			 (keys_t[]){MLX_KEY_ESCAPE, -1});
	bind_loop(g_hookservice, movement_bind, &g_camera, 0);
	bind_loop(g_hookservice, main_loop, &g_camera, 0);
	bind_loop(g_hookservice, head_bobbing_bind, NULL, 0);
	bind_loop(g_hookservice, automatic_doors_bind, NULL, 0);
	load_minimap();
	bind_loop(g_hookservice, fps_counter_bind, NULL, 0);

	mlx_loop(g_mlx);
	mlx_terminate(g_mlx);
}
