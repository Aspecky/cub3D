/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:58:38 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/13 17:20:50 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "consts.h"
#include <MLX42/MLX42.h>

static t_vector2 g_old_pos = {0, 0};

void cursor_hook(double xpos, double ypos, void *param)
{
	t_vector2 delta;
	double rads;
	double pitch_speed;
	int max_pitch;

	(void)param;
	delta.x = -(xpos - g_old_pos.x);
	delta.y = -(ypos - g_old_pos.y);
	rads = delta.x * CURSOR_SPEED * g_mlx->delta_time;
	g_camera.dir = vector2_rot(g_camera.dir, rads);
	g_camera.plane = vector2_rot(g_camera.plane, rads);
	pitch_speed = g_mlx->height / (2.0 * PLANE_SCALE);
	g_camera.pitch += (int)(delta.y * CURSOR_SPEED * pitch_speed * g_mlx->delta_time);
	max_pitch = (int)(g_mlx->height * MAX_PITCH_HSCALE);
	if (g_camera.pitch > max_pitch)
		g_camera.pitch = max_pitch;
	else if (g_camera.pitch < -max_pitch)
		g_camera.pitch = -max_pitch;
	g_old_pos.x = xpos;
	g_old_pos.y = ypos;
}
