/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_view_model.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:54:17 by mtarrih           #+#    #+#             */
/*   Updated: 2026/01/11 19:45:10 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <MLX42/MLX42.h>

bool	init_view_model(void)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;
	double			ratio;
	double			width;
	int				id;

	tex = mlx_load_png("assets/textures/view_model.png");
	if (!tex)
		return (false);
	img = mlx_texture_to_image(g_mlx, tex);
	mlx_delete_texture(tex);
	ratio = (double)img->height / img->width;
	width = (double)g_img->width * VIEW_MODEL_SCALE;
	mlx_resize_image(img, width, width * ratio);
	id = mlx_image_to_window(g_mlx, img, g_img->width / 2 - (img->width * 0.4),
			g_img->height - img->height + VIEW_MODEL_DEPTH);
	g_view_model.inst = img->instances + id;
	g_view_model.og_pos = (t_ivector2){g_view_model.inst->x,
		g_view_model.inst->y};
	return (true);
}
