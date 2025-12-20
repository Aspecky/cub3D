/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:22:52 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 16:30:41 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "mlx_aux/Vector2.h"
#include "player.h"

void rotate_bind(void *param)
{
	t_vector2 *plane;
	double dt;
	double rot_speed;

	(void)param;
	plane = &g_camera.plane;
	dt = g_mlx->delta_time;
	rot_speed = ROTSPEED * dt;
	if (mlx_is_key_down(g_mlx, MLX_KEY_RIGHT))
	{
		g_camera.dir = vector2_rot(g_camera.dir, -rot_speed);
		*plane = vector2_rot(*plane, -rot_speed);
	}
	if (mlx_is_key_down(g_mlx, MLX_KEY_LEFT))
	{
		g_camera.dir = vector2_rot(g_camera.dir, rot_speed);
		*plane = vector2_rot(*plane, rot_speed);
	}
}
