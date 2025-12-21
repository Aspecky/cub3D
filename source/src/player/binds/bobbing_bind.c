/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bobbing_bind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 20:59:33 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/21 22:11:01 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "player.h"
#include <math.h>

void bobbing_bind(void *param)
{
	static t_vector2 g_old_pos = {0, 0};
	static double dt = 0;
	double speed;
	double frequency;

	(void)param;
	if (g_player.pos.x != g_old_pos.x || g_player.pos.y != g_old_pos.y)
	{
		speed = vector2_mag(vector2_sub(g_player.pos, g_old_pos)) /
				g_mlx->delta_time;
		frequency = speed * 4.0;
		dt += g_mlx->delta_time * frequency;
		g_player.z = (int)(sin(dt) * 30);
		g_view_model.inst->y =
			g_view_model.og_pos.y + (int)(sin(dt + (M_PI_2)) * (VIEW_MODEL_DEPTH / 2.0));
	}
	g_old_pos = g_player.pos;
}
