/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:23:51 by mtarrih           #+#    #+#             */
/*   Updated: 2026/01/10 19:28:13 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "minimap.h"
#include <MLX42/MLX42.h>

static void	swap_int(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static mlx_image_t	*init_frame(uint32_t *frame_height, t_ivector2 frame_offset)
{
	mlx_texture_t	*frame_tex;
	mlx_image_t		*frame_img;

	frame_tex = mlx_load_png("assets/textures/porthole_window.png");
	if (!frame_tex)
		return (0);
	frame_img = mlx_texture_to_image(g_mlx, frame_tex);
	*frame_height = (uint32_t)((double)g_img->height * MINIMAP_SCALE);
	mlx_resize_image(frame_img, *frame_height, *frame_height);
	mlx_image_to_window(g_mlx, frame_img, frame_offset.x, frame_offset.y);
	return (frame_img);
}

static t_ivector2	calculate_minimap_offset(uint32_t frame_height,
		uint32_t minimap_height, t_ivector2 frame_offset)
{
	return ((t_ivector2){frame_offset.x + (int)((frame_height - minimap_height)
		/ 2) + (int)(frame_height * MINIMAP_OFFSET_X), frame_offset.y
		+ (int)((frame_height - minimap_height) / 2) + (int)(frame_height
			* MINIMAP_OFFSET_Y)});
}

static void	init_minimap_properties(uint32_t minimap_height,
		t_ivector2 minimap_offset)
{
	g_minimap.img = mlx_new_image(g_mlx, minimap_height, minimap_height);
	g_minimap.tile_size = (int)((double)minimap_height * MINIMAP_CELL_SCALE);
	g_minimap.tiles_visible = (int)minimap_height / g_minimap.tile_size;
	g_minimap.radius = (int)minimap_height / 2;
	g_minimap.radius_sq = g_minimap.radius * g_minimap.radius;
	g_minimap.center = (t_ivector2){(int)minimap_height / 2, (int)minimap_height
		/ 2};
	mlx_image_to_window(g_mlx, g_minimap.img, minimap_offset.x,
		minimap_offset.y);
}

bool	init_minimap(void)
{
	uint32_t	frame_height;
	uint32_t	minimap_height;
	t_ivector2	frame_offset;
	t_ivector2	minimap_offset;
	mlx_image_t	*frame_img;

	frame_offset = (t_ivector2){(int)((double)g_img->width * MINIMAP_OFFSET),
		(int)((double)g_img->height * MINIMAP_OFFSET)};
	frame_img = init_frame(&frame_height, frame_offset);
	if (!frame_img)
		return (false);
	minimap_height = (uint32_t)((double)frame_height * MINIMAP_CONTENT_SCALE);
	minimap_offset = calculate_minimap_offset(frame_height, minimap_height,
			frame_offset);
	init_minimap_properties(minimap_height, minimap_offset);
	swap_int(&frame_img->instances[0].z, &g_minimap.img->instances[0].z);
	return (true);
}
