/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_bind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:57:56 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/24 19:17:52 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "player.h"
#include "raycast.h"
#include <math.h>

static t_vector2	calculate_walk_direction(void)
{
	t_vector2	walk_dir;

	walk_dir = (t_vector2){0, 0};
	if (mlx_is_key_down(g_mlx, MLX_KEY_W))
		walk_dir = vector2_add(walk_dir, g_player.dir);
	if (mlx_is_key_down(g_mlx, MLX_KEY_A))
		walk_dir = vector2_add(walk_dir, vector2_rot(g_player.dir, M_PI_2));
	if (mlx_is_key_down(g_mlx, MLX_KEY_S))
		walk_dir = vector2_add(walk_dir, vector2_scale(g_player.dir, -1));
	if (mlx_is_key_down(g_mlx, MLX_KEY_D))
		walk_dir = vector2_add(walk_dir, vector2_rot(g_player.dir, -M_PI_2));
	return (walk_dir);
}

static t_vector2	calculate_collision_normal(t_vector2 walk_dir,
		t_raycast_result ray)
{
	t_vector2	normal;

	normal = (t_vector2){0, 0};
	if (ray.side == 0)
	{
		if (walk_dir.x > 0)
			normal.x = -1;
		else
			normal.x = 1;
	}
	else
	{
		if (walk_dir.y > 0)
			normal.y = -1;
		else
			normal.y = 1;
	}
	return (normal);
}

static void	handle_collision_slide(t_vector2 walk_dir, double walkspeed,
		double distance, t_raycast_result ray)
{
	t_vector2			normal;
	t_vector2			slide_dir;
	t_raycast_result	slide_ray;
	double				dot;

	normal = calculate_collision_normal(walk_dir, ray);
	dot = walk_dir.x * normal.x + walk_dir.y * normal.y;
	slide_dir = (t_vector2){walk_dir.x - dot * normal.x, walk_dir.y - dot
		* normal.y};
	slide_ray = circle_raycast(g_player.pos, vector2_unit(slide_dir), distance,
			HITBOX_RADIUS);
	if (!slide_ray.hit)
		g_player.pos = vector2_add(g_player.pos, vector2_scale(slide_dir,
					walkspeed));
}

static void	move_player(t_vector2 walk_dir, double walkspeed)
{
	t_vector2			pos;
	double				distance;
	t_raycast_result	ray;

	if (COLLISIONS)
	{
		pos = g_player.pos;
		distance = fmax(HITBOX_RADIUS, walkspeed);
		ray = circle_raycast(pos, walk_dir, distance, HITBOX_RADIUS);
		if (ray.hit)
			handle_collision_slide(walk_dir, walkspeed, distance, ray);
		else
			g_player.pos = vector2_add(g_player.pos, vector2_scale(walk_dir,
						walkspeed));
	}
	else
		g_player.pos = vector2_add(g_player.pos, vector2_scale(walk_dir,
					walkspeed));
}

void	walk_bind(void *param)
{
	t_vector2	walk_dir;

	(void)param;
	walk_dir = calculate_walk_direction();
	if (walk_dir.x == 0 && walk_dir.y == 0)
		return ;
	move_player(vector2_unit(walk_dir), g_player.walk_speed
		* g_mlx->delta_time);
}
