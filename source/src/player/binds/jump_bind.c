/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_bind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:20:04 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 16:19:45 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "consts.h"
#include <MLX42/MLX42.h>
#include <math.h>
#include <stdbool.h>

static double lerp(double a, double b, double t)
{
	return (a + (b - a) * t);
}

static double easeOut(double t)
{
	return (sin((t * M_PI) / 2));
}

static double easeIn(double t)
{
	return (1 - cos((t * M_PI) / 2));
}

void jump_bind(void *param)
{
	static bool animating = false;
	static bool jumping = false;
	static bool falling = false;
	static double dt = 0;
	static double hold_time = 0;
	static double jump_boost = 0;
	double alpha;

	(void)param;
	if (!animating && mlx_is_key_down(g_mlx, MLX_KEY_SPACE))
	{
		animating = true;
		jumping = false;
		falling = false;
		jump_boost = 0;
		hold_time = 0;
		dt = 0;
	}
	if (!animating)
		return;

	double squat_depth = -(double)g_img->height * SQUAT_DEPTH;

	if (!jumping)
	{
		g_camera.walk_speed = WALKSPEED * 0.4;
		dt += g_mlx->delta_time;
		alpha = fmin(dt / SQUAT_TIME, 1);
		g_camera.z = (int)(lerp(0, squat_depth, easeOut(alpha)));
		if (alpha == 1)
		{
			if (mlx_is_key_down(g_mlx, MLX_KEY_SPACE))
			{
				hold_time += g_mlx->delta_time;
				jump_boost =
					JUMP_BOOST_MAX * fmin(hold_time / JUMP_BOOST_TIME, 1);
			} else
			{
				dt = 0;
				jumping = true;
				g_camera.walk_speed = WALKSPEED;
			}
		}
	} else
	{
		double jump_target = (double)g_img->height * (JUMP_HEIGHT + jump_boost);

		if (!falling)
		{
			dt += g_mlx->delta_time;
			alpha = fmin(dt / (JUMP_TIME / 2), 1);
			g_camera.z = (int)lerp(squat_depth, jump_target, easeOut(alpha));
			if (alpha == 1)
			{
				dt = 0;
				falling = true;
			}
		} else
		{
			dt += g_mlx->delta_time;
			alpha = fmin(dt / (JUMP_TIME / 2), 1);
			g_camera.z = (int)lerp(jump_target, 0, easeIn(alpha));
			if (alpha == 1)
				animating = false;
		}
	}
}
