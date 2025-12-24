/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:59:59 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/21 19:03:41 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "loaders.h"
#include "player.h"

bool	load_player(t_vector2 position, t_vector2 direction)
{
	if (!init_view_model())
		return (false);
	g_player.cam_plane = (t_vector2){direction.y * PLANE_SCALE, -direction.x
		* PLANE_SCALE};
	g_player.pos = position;
	g_player.dir = direction;
	g_player.pitch = 0;
	g_player.z = 0;
	g_player.walk_speed = WALKSPEED;
	mlx_set_mouse_pos(g_mlx, 0, 0);
	mlx_set_cursor_mode(g_mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(g_mlx, cursor_hook, 0);
	bind_loop(g_hookservice, rotate_bind, 0, 0);
	bind_loop(g_hookservice, walk_bind, 0, 0);
	bind_loop(g_hookservice, bobbing_bind, 0, 0);
	bind_loop(g_hookservice, jump_bind, 0, 0);
	return (true);
}
