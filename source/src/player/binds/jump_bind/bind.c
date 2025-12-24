/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:20:04 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/24 21:08:03 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "easing.h"
#include "player.h"
#include <MLX42/MLX42.h>
#include <math.h>
#include <stdbool.h>

static void	handle_squat(t_jump_state *state, double squat_depth)
{
	double	alpha;

	g_player.walk_speed = WALKSPEED * 0.4;
	state->dt += g_mlx->delta_time;
	alpha = fmin(state->dt / SQUAT_TIME, 1);
	g_player.z = (int)(lerp(0, squat_depth, ease_out(alpha)));
	if (alpha == 1)
	{
		if (mlx_is_key_down(g_mlx, MLX_KEY_SPACE))
		{
			state->hold_time += g_mlx->delta_time;
			state->jump_boost = JUMP_BOOST_MAX * fmin(state->hold_time
					/ JUMP_BOOST_TIME, 1);
		}
		else
		{
			state->dt = 0;
			state->jumping = true;
			g_player.walk_speed = WALKSPEED;
		}
	}
}

static void	handle_jump_up(t_jump_state *state, double squat_depth,
		double jump_target)
{
	double	alpha;

	state->dt += g_mlx->delta_time;
	alpha = fmin(state->dt / (JUMP_TIME / 2), 1);
	g_player.z = (int)lerp(squat_depth, jump_target, ease_out(alpha));
	if (alpha == 1)
	{
		state->dt = 0;
		state->falling = true;
	}
}

static void	handle_fall_down(t_jump_state *state, double jump_target)
{
	double	alpha;

	state->dt += g_mlx->delta_time;
	alpha = fmin(state->dt / (JUMP_TIME / 2), 1);
	g_player.z = (int)lerp(jump_target, 0, ease_in(alpha));
	if (alpha == 1)
		state->animating = false;
}

void	jump_bind(void *param)
{
	static t_jump_state	state = {0, 0, 0, 0, 0, 0};
	double				squat_depth;
	double				jump_target;

	(void)param;
	if (!state.animating && mlx_is_key_down(g_mlx, MLX_KEY_SPACE))
		state = (t_jump_state){true, false, false, 0, 0, 0};
	if (!state.animating)
		return ;
	squat_depth = -(double)g_img->height * SQUAT_DEPTH;
	if (!state.jumping)
		handle_squat(&state, squat_depth);
	else
	{
		jump_target = (double)g_img->height * (JUMP_HEIGHT + state.jump_boost);
		if (!state.falling)
			handle_jump_up(&state, squat_depth, jump_target);
		else
			handle_fall_down(&state, jump_target);
	}
}
