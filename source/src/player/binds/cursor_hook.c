/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:58:38 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 17:41:52 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "player.h"
#include <MLX42/MLX42.h>

void	cursor_hook(double xpos, double ypos, void *param)
{
	static t_vector2	old_pos = {0, 0};
	t_vector2			delta;
	double				rads;
	double				pitch_speed;
	int					max_pitch;

	(void)param;
	delta.x = -(xpos - old_pos.x);
	delta.y = -(ypos - old_pos.y);
	rads = delta.x * CURSOR_SPEED * g_mlx->delta_time;
	g_player.dir = vector2_rot(g_player.dir, rads);
	g_player.cam_plane = vector2_rot(g_player.cam_plane, rads);
	pitch_speed = g_mlx->height / (2.0 * PLANE_SCALE);
	g_player.pitch += (int)(delta.y * CURSOR_SPEED * pitch_speed
			* g_mlx->delta_time);
	max_pitch = (int)(g_mlx->height * MAX_PITCH_HSCALE);
	if (g_player.pitch > max_pitch)
		g_player.pitch = max_pitch;
	else if (g_player.pitch < -max_pitch)
		g_player.pitch = -max_pitch;
	old_pos.x = xpos;
	old_pos.y = ypos;
}
