/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:39:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/11/30 18:37:26 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTS_H
# define CONSTS_H

# define MONITOR_SCALE 0.75
# define WALKSPEED 4 // squares / second
# define ROTSPEED 3 // radians / second
# define HITBOX_RADIUS 0.1
# define CURSOR_SPEED 0.01 // radians / pixel
# define COLLISIONS true

# define VIEW_MODEL_SCALE 0.7
# define VIEW_MODEL_DEPTH 100 // pixels

#include <MLX42/MLX42.h>
#include <mlx_aux/Color4.h>
#include <mlx_aux/Vector2.h>

extern mlx_t *g_mlx;
extern mlx_image_t *g_img;

extern struct s_camera {
	t_vector2 pos;
	t_vector2 dir;
	t_vector2 plane;
} g_camera;

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

extern struct s_view_model {
	mlx_image_t *img;
	mlx_instance_t *inst;
	t_ivector2 og_pos;
} g_view_model;

#endif
