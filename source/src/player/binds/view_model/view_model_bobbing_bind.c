/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_model_bobbing_bind.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:02:24 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 17:14:12 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <math.h>
#include "consts.h"

void view_model_bobbing_bind(void *param)
{
	static t_vector2 g_old_pos = {0, 0};
	static double dt = 0;
	double speed;
	double frequency;
	double y_offset;

	(void)param;
	if (g_camera.pos.x != g_old_pos.x || g_camera.pos.y != g_old_pos.y)
	{
		speed = vector2_mag(vector2_sub(g_camera.pos, g_old_pos)) /
				g_mlx->delta_time;
		frequency = speed * 2.0;
		dt += g_mlx->delta_time * frequency;
		y_offset = sin(dt) * (VIEW_MODEL_DEPTH / 2.0);
		g_view_model.inst->y = g_view_model.og_pos.y + (int)y_offset;
	} else
	{
		g_view_model.inst->y = g_view_model.og_pos.y;
		dt = 0;
	}
	g_old_pos = g_camera.pos;
}
