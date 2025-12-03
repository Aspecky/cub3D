/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:57:56 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/03 15:35:16 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bindings.h"
#include "consts.h"
#include "utils.h"
#include <MLX42/MLX42.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

static t_raycast_result circle_raycast(t_vector2 origin, t_vector2 direction,
									   double distance, double radius)
{
	int num_rays = 12;
	t_raycast_result shortest_ray;
	t_raycast_result ray;
	t_vector2 start;
	double angle;
	int i;

	shortest_ray = (t_raycast_result){.hit = false, .distance = DBL_MAX};
	i = 0;
	while (i < num_rays)
	{
		angle = ((double)i / num_rays) * M_PI * 2;
		start = (t_vector2){origin.x + cos(angle) * radius,
							origin.y + sin(angle) * radius};
		ray = raycast(start, direction, distance);
		if (ray.hit)
		{
			ray.distance = vector2_mag(vector2_sub(ray.position, origin));
			if (ray.distance < shortest_ray.distance)
				shortest_ray = ray;
		}
		i++;
	}

	return (shortest_ray);
}

static void rotate_player(void)
{
	t_vector2 *plane;
	double dt;
	double rot_speed;

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

static void move_player(void)
{
	t_vector2 walk_dir;
	t_vector2 new_pos;
	double dt;

	walk_dir = (t_vector2){0, 0};
	dt = g_mlx->delta_time;
	if (mlx_is_key_down(g_mlx, MLX_KEY_W))
		walk_dir = vector2_add(walk_dir, g_camera.dir);
	if (mlx_is_key_down(g_mlx, MLX_KEY_A))
		walk_dir = vector2_add(walk_dir, vector2_rot(g_camera.dir, M_PI_2));
	if (mlx_is_key_down(g_mlx, MLX_KEY_S))
		walk_dir = vector2_add(walk_dir, vector2_scale(g_camera.dir, -1));
	if (mlx_is_key_down(g_mlx, MLX_KEY_D))
		walk_dir = vector2_add(walk_dir, vector2_rot(g_camera.dir, -M_PI_2));

	if (walk_dir.x == 0 && walk_dir.y == 0)
		return;
	walk_dir = vector2_unit(walk_dir);

	double walkspeed;
	walkspeed = WALKSPEED * dt;

	if (COLLISIONS)
	{
		t_vector2 pos;
		double distance;
		pos = g_camera.pos;

		distance = fmax(HITBOX_RADIUS, walkspeed);
		t_raycast_result ray =
			circle_raycast(pos, walk_dir, distance, HITBOX_RADIUS);
		if (ray.hit)
		{
			// Calculate wall normal
			t_vector2 normal = {0, 0};
			if (ray.side == 0)
				normal.x = (walk_dir.x > 0) ? -1 : 1;
			else
				normal.y = (walk_dir.y > 0) ? -1 : 1;

			// Project movement onto wall surface for sliding
			// slide_dir = walk_dir - (walk_dir · normal) * normal
			double dot = walk_dir.x * normal.x + walk_dir.y * normal.y;
			t_vector2 slide_dir = {walk_dir.x - dot * normal.x,
								   walk_dir.y - dot * normal.y};

			// Try moving in the slide direction
			t_raycast_result slide_ray = circle_raycast(
				pos, vector2_unit(slide_dir), distance, HITBOX_RADIUS);

			if (!slide_ray.hit)
				g_camera.pos = vector2_add(g_camera.pos,
										   vector2_scale(slide_dir, walkspeed));

		} else
			g_camera.pos =
				vector2_add(g_camera.pos, vector2_scale(walk_dir, walkspeed));
	} else
	{
		new_pos = vector2_add(g_camera.pos, vector2_scale(walk_dir, walkspeed));
		g_camera.pos = new_pos;
	}
}

void movement_bind(void *param)
{
	(void)param;
	rotate_player();
	move_player();
}
