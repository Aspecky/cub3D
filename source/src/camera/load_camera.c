/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:59:20 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/14 14:42:56 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "consts.h"
#include "loaders.h"
#include <MLX42/MLX42.h>

struct s_camera g_camera;

bool load_camera(t_vector2 position, t_vector2 direction)
{
	g_camera.plane =
		(t_vector2){direction.y * PLANE_SCALE, -direction.x * PLANE_SCALE};
	g_camera.pos = position;
	g_camera.dir = direction;
	g_camera.pitch = 0;
	g_camera.z = 0;
	g_camera.walk_speed = WALKSPEED;
	// mlx_set_mouse_pos(g_mlx, 0, 0);
	mlx_set_cursor_mode(g_mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(g_mlx, cursor_hook, 0);
	bind_loop(g_hookservice, jump_bind, 0, 0);

	return (true);
}
