/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:39:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/11/27 16:38:57 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTS_H
# define CONSTS_H

# define MONITOR_SCALE 75
# define WALKSPEED 1 // squares per second
# define ROTSPEED 3 // radians per second

# define COLLISIONS true

#include <mlx42.h>
#include <Color4.h>

extern mlx_t *g_mlx;
extern mlx_image_t *g_canvas;

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
