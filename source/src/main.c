/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:16:05 by mtarrih           #+#    #+#             */
/*   Updated: 2025/11/29 19:20:50 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx_aux/HookService.h>
#include "bindings.h"
#include "consts.h"
#include "utils.h"
#include <mlx_aux/Color4.h>
#include <MLX42/MLX42.h>
#include <ftlibc/ft_string.h>
#include <math.h>
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

// world_map[y][x]

int world_map[][5] = {
	{1, 1, 1, 1, 1}, //
	{1, 0, 0, 0, 1}, //
	{1, 0, 0, 1, 1}, //
	{1, 0, 1, 1, 1}, //
	{1, 0, 0, 0, 1}, //
	{1, 1, 1, 1, 1}, //
};
int rows = sizeof(world_map) / sizeof(world_map[0]);
int cols = sizeof(world_map[0]) / sizeof(world_map[0][0]);

// int map_width
// int world_map[][7] = {
// 	{1, 1, 1, 1, 1, 1, 1}, //
// 	{1, 0, 0, 0, 0, 0, 1}, //
// 	{1, 0, 0, 1, 0, 0, 1}, //
// 	{1, 0, 1, 1, 0, 0, 1}, //
// 	{1, 0, 0, 0, 0, 0, 1}, //
// 	{1, 1, 1, 1, 1, 1, 1}, //
// };

mlx_t *g_mlx;
mlx_image_t *g_img;
struct s_theme g_theme;
struct s_map g_map;
struct s_camera g_camera;

static mlx_t *open_scaled_window(const char *title)
{
	mlx_t *mlx;
	int32_t width;
	int32_t height;

	mlx = mlx_init(1, 1, title, 0);
	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(mlx, (width * MONITOR_SCALE) / 100,
						(height * MONITOR_SCALE) / 100);
	mlx_set_window_pos(mlx, width / 2 - mlx->width / 2,
					   height / 2 - mlx->height / 2);
	return (mlx);
}

static void draw_ceiling(int x, int y_end)
{
	int y;

	y = 0;
	while (y < y_end)
	{
		mlx_put_pixel(g_img, x, y, g_theme.ceiling);
		y++;
	}
}

static void draw_floor(int x, int y_start)
{
	int y;

	y = y_start;
	while (y < (int)g_img->height)
	{
		mlx_put_pixel(g_img, x, y, g_theme.floor);
		y++;
	}
}

static void main_loop(void *arg)
{
	uint32_t x;

	(void)arg;
	x = 0;
	mlx_clear_image(g_img);
	while (x < g_img->width)
	{
		double camX = 2.0 * x / g_img->width - 1;
		t_vector2 raydir =
			vector2_add(g_camera.dir, vector2_scale(g_camera.plane, camX));
		t_raycast_result ray = raycast(g_camera.pos, raydir, 10.0);

		if (ray.hit)
		{
			int h = (int)g_img->height;
			int lineHeight = (int)(h / ray.distance);

			int drawStart = -lineHeight / 2 + h / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + h / 2;
			if (drawEnd >= h)
				drawEnd = h - 1;

			// calculate value of wallX
			double wallX; // where exactly the wall was hit
			if (ray.side == 0)
				wallX = g_camera.pos.y + ray.distance * raydir.y;
			else
				wallX = g_camera.pos.x + ray.distance * raydir.x;
			wallX -= floor((wallX));

			// x coordinate on the texture
			mlx_texture_t *tex;

			if (ray.side == 0)
			{
				if (raydir.x < 0)
					tex = g_theme.ea;
				else
					tex = g_theme.we;
			} else
			{
				if (raydir.y < 0)
					tex = g_theme.no;
				else
					tex = g_theme.so;
			}

			uint32_t texX = (uint32_t)(wallX * tex->width);
			if (ray.side == 0 && raydir.x > 0)
				texX = tex->width - texX - 1;
			if (ray.side == 1 && raydir.y < 0)
				texX = tex->width - texX - 1;

			draw_ceiling((int)x, drawEnd);

			double step = (double)tex->height / lineHeight;
			double texPos = (int)(drawStart - h / 2 + lineHeight / 2) * step;
			for (int y = drawStart; y < drawEnd; y++)
			{
				uint32_t texY = (uint32_t)texPos;
				// uint32_t texY = (uint32_t)texPos & (tex->height - 1);
				texPos += step;

				// Get pixel from texture (4 bytes per pixel: RGBA)
				uint32_t pixel_index = (tex->width * texY + texX) * 4;
				uint8_t r = tex->pixels[pixel_index + 0];
				uint8_t g = tex->pixels[pixel_index + 1];
				uint8_t b = tex->pixels[pixel_index + 2];
				uint8_t a = tex->pixels[pixel_index + 3];

				// Write directly to buffer instead of using mlx_put_pixel
				uint32_t buffer_index = (g_img->width * y + x) * 4;
				g_img->pixels[buffer_index + 0] = r;
				g_img->pixels[buffer_index + 1] = g;
				g_img->pixels[buffer_index + 2] = b;
				g_img->pixels[buffer_index + 3] = a;
			}
			draw_floor(x, drawEnd);
		}
		x++;
	}
}

int main(void)
{
	t_hookservice *hookservice;

	g_mlx = open_scaled_window("cub3d");
	g_img = mlx_new_image(g_mlx, g_mlx->width, g_mlx->height);
	mlx_image_to_window(g_mlx, g_img, 0, 0);

	g_camera.pos = (t_vector2){2.5, 1.1};
	g_camera.dir = (t_vector2){-1, 0};
	g_camera.plane = (t_vector2){0, 0.66};

	{
		mlx_texture_t *tex = mlx_load_png("assets/net.png");
		mlx_image_t *img = mlx_texture_to_image(g_mlx, tex);
		double ratio = (double)img->height / img->width;
		mlx_resize_image(img, 2000, 2000 * ratio);
		int id = mlx_image_to_window(g_mlx, img, 0, 0);

		g_camera.inst = img->instances[id];
	}

	g_theme.ceiling = color4_from_hex("87CEEB");
	g_theme.floor = color4_from_hex("9B7653");
	g_theme.no = mlx_load_png("assets/North.png");
	g_theme.ea = mlx_load_png("assets/East.png");
	g_theme.so = mlx_load_png("assets/South.png");
	g_theme.we = mlx_load_png("assets/West.png");
	mlx_resize_texture(g_mlx, g_theme.no, 64, 64);
	mlx_resize_texture(g_mlx, g_theme.ea, 64, 64);
	mlx_resize_texture(g_mlx, g_theme.so, 64, 64);
	mlx_resize_texture(g_mlx, g_theme.we, 64, 64);

	g_map.width = sizeof(world_map[0]) / sizeof(world_map[0][0]);
	g_map.height = sizeof(world_map) / sizeof(world_map[0]);
	g_map.buffer = malloc(sizeof(int) * g_map.width * g_map.height);
	for (int x = 0; x < g_map.width; x++)
		for (int y = 0; y < g_map.height; y++)
			g_map.buffer[x * g_map.height + y] =
				world_map[g_map.height - 1 - y][x];

	hookservice = hookservice_init(g_mlx);
	bind_key(hookservice, close_window_bind, NULL,
			 (keys_t[]){MLX_KEY_ESCAPE, -1});
	bind_loop(hookservice, movement_bind, &g_camera, 0);
	bind_loop(hookservice, main_loop, &g_camera, 0);

	mlx_set_mouse_pos(g_mlx, 0, 0);
	mlx_set_cursor_mode(g_mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(g_mlx, cursor_hook, 0);

	mlx_loop(g_mlx);
	mlx_terminate(g_mlx);
}
