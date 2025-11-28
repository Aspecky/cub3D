/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:39:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/11/28 16:52:06 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTS_H
# define CONSTS_H

# define MONITOR_SCALE 75
# define WALKSPEED 4 // squares / second
# define ROTSPEED 3 // radians / second
# define HITBOX_RADIUS 0.1
# define CURSOR_SPEED 0.01 // radians / pixel
# define COLLISIONS true

#include <mlx42.h>
#include <Color4.h>
#include "types.h"

extern mlx_t *g_mlx;
extern mlx_image_t *g_canvas;
extern t_camera g_camera;

extern struct s_map {
	int width;
	int height;
	int *buffer;
} g_map;

extern struct s_theme {
	mlx_texture_t *no;
	mlx_texture_t *so;
	mlx_texture_t *we;
	mlx_texture_t *ea;
	t_color4	ceiling;
	t_color4	floor;
} g_theme;

#endif
