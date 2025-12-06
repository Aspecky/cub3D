/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:16:05 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/06 20:11:32 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
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

double world_map[][7] = {
	{1, 1, 1, 1, 1, 1, 1},	 //
	{1, 1, 0, 0, 0, 0, 1},	 //
	{1, 1, 0, 0, 0, 0, 1},	 //
	{1, 1, 0, 0, 0, 0, 1},	 //
	{1, 1, 2, 1, 1, 0, 1}, //
	{1, 0, 0, 0, 1, 2, 1},	 //
	{1.8, 0, 0, 0, 0, 0, 1},	 //
	{1, 1, 1, 1, 1, 1, 1},	 //
};
int rows = sizeof(world_map) / sizeof(world_map[0]);
int cols = sizeof(world_map[0]) / sizeof(world_map[0][0]);

mlx_t *g_mlx;
mlx_image_t *g_img;
struct s_theme g_theme;
struct s_map g_map;
struct s_camera g_camera;
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
	uint32_t x;
	uint32_t y;
	uint32_t half_height;

	half_height = g_img->height / 2;
	y = 0;
	while (y < g_img->height)
	{
		x = 0;
		while (x < g_img->width)
		{
			if (y < half_height)
				mlx_put_pixel(g_img, x, y, g_theme.ceiling);
			else
				mlx_put_pixel(g_img, x, y, g_theme.floor);
			x++;
		}
		y++;
	}
}

static mlx_texture_t *cell_type_to_texture(t_raycast_result ray,
										   t_vector2 direction)
{
	if (ray.cell_type == CELL_WALL)
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
	} else if (ray.cell_type == CELL_DOOR)
		return g_theme.door;
	return (g_theme.no);
}

static void main_loop(void *arg)
{
	uint32_t x;

	(void)arg;
	x = 0;
	draw_floor_and_ceiling();
	while (x < g_img->width)
	{
		double camX = 2.0 * x / g_img->width - 1;
		{
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

				raypos = vector2_add(ray.position,
									 vector2_scale(unit_raydir, 0.001));
				raydis -= ray.distance;
				traveled_distance += ray.distance;

				rays_count++;
				if (ray.cell_opacity >= 1)
					break;
			}

			size_t i = rays_count;
			while (i-- > 0)
			{
				ray = rays[i];

				int h = (int)g_img->height;
				int lineHeight = (int)(h / (distances[i] + ray.distance));

				int drawStart = -lineHeight / 2 + h / 2;
				if (drawStart < 0)
					drawStart = 0;
				int drawEnd = lineHeight / 2 + h / 2;
				if (drawEnd >= h)
					drawEnd = h - 1;

				mlx_texture_t *tex = cell_type_to_texture(ray, raydir);

				// calculate value of wallX
				double wall_x; // where exactly the wall was hit
				if (ray.side == 0)
					wall_x = ray.position.y;
				else
					wall_x = ray.position.x;
				wall_x -= floor((wall_x));

				uint32_t tex_x = (uint32_t)(wall_x * tex->width);
				if (ray.side == 0 && raydir.x > 0)
					tex_x = tex->width - tex_x - 1;
				if (ray.side == 1 && raydir.y < 0)
					tex_x = tex->width - tex_x - 1;

				double step = (double)tex->height / lineHeight;
				double texPos =
					(int)(drawStart - h / 2 + lineHeight / 2) * step;
				double new_alpha = ray.cell_opacity;

				for (int y = drawStart; y < drawEnd; y++)
				{
					uint32_t tex_y = (uint32_t)texPos & (tex->height - 1);
					texPos += step;

					uint32_t img_idx = (y * g_img->width + x) * 4;
					uint32_t tex_idx = (tex_y * tex->width + tex_x) * 4;

					uint8_t cur_red, cur_grn, cur_blu;
					uint8_t new_red, new_grn, new_blu;

					cur_red = g_img->pixels[img_idx + 0];
					cur_grn = g_img->pixels[img_idx + 1];
					cur_blu = g_img->pixels[img_idx + 2];

					new_red = tex->pixels[tex_idx + 0];
					new_grn = tex->pixels[tex_idx + 1];
					new_blu = tex->pixels[tex_idx + 2];

					g_img->pixels[img_idx + 0] =
						new_red * new_alpha + cur_red * (1 - new_alpha);
					g_img->pixels[img_idx + 1] =
						new_grn * new_alpha + cur_grn * (1 - new_alpha);
					g_img->pixels[img_idx + 2] =
						new_blu * new_alpha + cur_blu * (1 - new_alpha);
					g_img->pixels[img_idx + 3] = 255;
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
	t_hookservice *hookservice;

	g_mlx = open_scaled_window("cub3d");
	g_img = mlx_new_image(g_mlx, g_mlx->width, g_mlx->height);
	mlx_image_to_window(g_mlx, g_img, 0, 0);

	g_camera.pos = (t_vector2){2.5, 1.5};
	g_camera.dir = (t_vector2){-1, 0};
	g_camera.plane = (t_vector2){0, 0.66};
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

	g_map.width = sizeof(world_map[0]) / sizeof(world_map[0][0]);
	g_map.height = sizeof(world_map) / sizeof(world_map[0]);
	g_map.buffer = malloc(sizeof(*g_map.buffer) * g_map.width * g_map.height);
	for (int x = 0; x < g_map.width; x++)
	{
		for (int y = 0; y < g_map.height; y++)
		{
			double cell_value = world_map[g_map.height - 1 - y][x];
			g_map.buffer[x * g_map.height + y].cell_type = (int)cell_value;
			g_map.buffer[x * g_map.height + y].opacity =
				cell_value - (int)cell_value;
			if (g_map.buffer[x * g_map.height + y].opacity == 0)
				g_map.buffer[x * g_map.height + y].opacity = 1;
		}
	}

	g_doors.count = 0;
	for (int i = 0; i < g_map.width * g_map.height; i++)
	{
		if (g_map.buffer[i].cell_type == CELL_DOOR)
			g_doors.count++;
	}
	g_doors.locations = malloc(sizeof(t_ivector2) * g_doors.count);
	g_doors.count = 0;
	for (int x = 0; x < g_map.width; x++)
	{
		for (int y = 0; y < g_map.height; y++)
		{
			if (g_map.buffer[x * g_map.height + y].cell_type == CELL_DOOR)
			{
				g_doors.locations[g_doors.count] = (t_ivector2){x, y};
				g_doors.count++;
			}
		}
	}

	hookservice = hookservice_init(g_mlx);
	bind_key(hookservice, close_window_bind, NULL,
			 (keys_t[]){MLX_KEY_ESCAPE, -1});
	bind_loop(hookservice, movement_bind, &g_camera, 0);
	bind_loop(hookservice, main_loop, &g_camera, 0);
	bind_loop(hookservice, head_bobbing_bind, NULL, 0);
	bind_loop(hookservice, automatic_doors_bind, NULL, 0);

	mlx_set_mouse_pos(g_mlx, 0, 0);
	// mlx_set_cursor_mode(g_mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(g_mlx, cursor_hook, 0);

	mlx_loop(g_mlx);
	mlx_terminate(g_mlx);
}
