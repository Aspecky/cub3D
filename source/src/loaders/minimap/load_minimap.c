/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:55:05 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/14 17:17:38 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
#include "loaders.h"
#include "minimap.h"
#include <MLX42/MLX42.h>

static void swap_int(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void init_minimap(void)
{
	uint32_t frame_height;
	uint32_t minimap_height;
	t_ivector2 frame_offset;
	t_ivector2 minimap_offset;
	mlx_texture_t *frame_tex;
	mlx_image_t *frame_img;

	frame_height = (uint32_t)((double)g_img->height * MINIMAP_SCALE);
	frame_offset = (t_ivector2){(int)((double)g_img->width * MINIMAP_OFFSET),
								(int)((double)g_img->height * MINIMAP_OFFSET)};

	frame_tex = mlx_load_png("assets/porthole_window.png");
	frame_img = mlx_texture_to_image(g_mlx, frame_tex);
	mlx_resize_image(frame_img, frame_height, frame_height);
	mlx_image_to_window(g_mlx, frame_img, frame_offset.x, frame_offset.y);

	minimap_height = (uint32_t)((double)frame_height * MINIMAP_CONTENT_SCALE);
	minimap_offset = (t_ivector2){
		frame_offset.x + (int)((frame_height - minimap_height) / 2) +
			(int)(frame_height * MINIMAP_OFFSET_X),
		frame_offset.y + (int)((frame_height - minimap_height) / 2) +
			(int)(frame_height * MINIMAP_OFFSET_Y)};

	g_minimap.img = mlx_new_image(g_mlx, minimap_height, minimap_height);
	g_minimap.tile_size = (int)((double)minimap_height * MINIMAP_CELL_SCALE);
	g_minimap.tiles_visible = (int)minimap_height / g_minimap.tile_size;
	g_minimap.radius = (int)minimap_height / 2;
	g_minimap.center =
		(t_ivector2){(int)minimap_height / 2, (int)minimap_height / 2};
	mlx_image_to_window(g_mlx, g_minimap.img, minimap_offset.x,
						minimap_offset.y);

	swap_int(&frame_img->instances[0].z, &g_minimap.img->instances[0].z);
}

bool load_minimap(void)
{
	init_minimap();
	bind_loop(g_hookservice, minimap_bind, NULL, 0);
	return (true);
}
