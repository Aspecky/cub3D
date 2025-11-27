/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:57:56 by mtarrih           #+#    #+#             */
/*   Updated: 2025/11/27 18:00:23 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
#include "types.h"
#include "utils.h"
#include <mlx42.h>
#include <stdio.h>

static void rotate_player(t_env *env)
{
	t_player *player;
	t_vector2 *plane;
	double dt;
	double rot_speed;

	player = &env->player;
	plane = &env->player.plane;
	dt = g_mlx->delta_time;
	rot_speed = ROTSPEED * dt;
	if (mlx_is_key_down(g_mlx, MLX_KEY_RIGHT))
	{
		player->dir = vector2_rot(player->dir, -rot_speed);
		*plane = vector2_rot(*plane, -rot_speed);
	}
	if (mlx_is_key_down(g_mlx, MLX_KEY_LEFT))
	{
		player->dir = vector2_rot(player->dir, rot_speed);
		*plane = vector2_rot(*plane, rot_speed);
	}
}

static void move_player(t_env *env)
{
	t_player *player;
	t_vector2 walk_dir;
	t_vector2 new_pos;
	double dt;

	player = &env->player;
	walk_dir = (t_vector2){0, 0};
	dt = g_mlx->delta_time;
	if (mlx_is_key_down(g_mlx, MLX_KEY_W))
		walk_dir = vector2_add(walk_dir, player->dir);
	if (mlx_is_key_down(g_mlx, MLX_KEY_A))
		walk_dir =
			vector2_add(walk_dir, (t_vector2){-player->dir.y, player->dir.x});
	if (mlx_is_key_down(g_mlx, MLX_KEY_S))
		walk_dir = vector2_add(walk_dir, vector2_scale(player->dir, -1));
	if (mlx_is_key_down(g_mlx, MLX_KEY_D))
		walk_dir =
			vector2_add(walk_dir, (t_vector2){player->dir.y, -player->dir.x});

	if (walk_dir.x == 0 && walk_dir.y == 0)
		return;

	if (COLLISIONS)
	{
		walk_dir = vector2_unit(walk_dir);

		t_vector2 pos;
		double walkspeed;
		pos = player->pos;

		walkspeed = WALKSPEED * dt;
		t_raycast_result ray = raycast(pos, walk_dir, 100.0);
		if (ray.hit)
		{
			t_vector2 normal = {0, 0};
			if (ray.side == 0)
			{
				if (walk_dir.x > 1)
					normal.x = -1;
				else
					normal.x = 1;
			} else
			{
				if (walk_dir.y > 1)
					normal.y = -1;
				else
					normal.y = 1;
			}
			t_vector2 inter =
				vector2_add(pos, vector2_scale(walk_dir, ray.distance - 0.1));
			player->pos = inter;
		} else
			player->pos =
				vector2_add(player->pos, vector2_scale(walk_dir, walkspeed));
		// if (ray.hit)
		// {
		// 	printf("%.2f => %.2f\n", walkspeed, ray.distance);
		// 	// walkspeed = ray.distance;
		// }
		// new_pos = vector2_add(pos, vector2_scale(walk_dir, walkspeed));
		// player->pos = new_pos;
		// if (g_map.buffer[(int)player->pos.y * g_map.width + (int)new_pos.x]
		// == 0) 	player->pos = (t_vector2){new_pos.x, player->pos.y}; if
		// (g_map.buffer[(int)new_pos.y * g_map.width + (int)player->pos.x] ==
		// 0) 	player->pos = (t_vector2){player->pos.x, new_pos.y};
	} else
	{
		new_pos =
			vector2_add(player->pos, vector2_scale(walk_dir, WALKSPEED * dt));
		player->pos = new_pos;
	}
}

void movement_bind(void *param)
{
	t_env *env;

	env = param;
	rotate_player(env);
	move_player(env);
}
