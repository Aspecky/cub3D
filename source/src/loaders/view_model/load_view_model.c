/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_view_model.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 18:01:10 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/14 18:03:45 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
#include "loaders.h"
#include <MLX42/MLX42.h>

bool load_view_model(void)
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
	bind_loop(g_hookservice, head_bobbing_bind, NULL, 0);
	return (true);
}
