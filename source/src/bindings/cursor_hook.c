/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:58:38 by mtarrih           #+#    #+#             */
/*   Updated: 2025/11/30 18:17:00 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
#include <math.h>
#include <MLX42/MLX42.h>

static double g_old_x = 0;

void cursor_hook(double xpos, double ypos, void *param)
{
	double delta_x;
	double rads;

	(void)param;
	(void)ypos;
	delta_x = -(xpos - g_old_x);
	rads = delta_x * CURSOR_SPEED * g_mlx->delta_time;
	g_camera.dir = vector2_rot(g_camera.dir, rads);
	g_camera.plane = vector2_rot(g_camera.plane, rads);
	g_old_x = xpos;
}
