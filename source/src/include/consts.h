/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:39:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/11 22:52:24 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTS_H
# define CONSTS_H

# include "types.h"
# include <MLX42/MLX42.h>
# include <mlx_aux/Color4.h>
# include <mlx_aux/Vector2.h>
# include <mlx_aux/HookService.h>

# define MONITOR_SCALE 0.75
# define WALKSPEED 3 // squares / second
# define ROTSPEED 3    // radians / second
# define HITBOX_RADIUS 0.1
# define CURSOR_SPEED 0.01 // radians / pixel
# define COLLISIONS true

# define VIEW_MODEL_SCALE 0.7
# define VIEW_MODEL_DEPTH 100 // pixels

# define MINIMAP_SCALE 0.3
# define MINIMAP_CELL_SCALE 0.1
# define MINIMAP_COLOR_WALL 0x00CED1FF
# define MINIMAP_COLOR_DOOR 0xFF69B4FF
# define MINIMAP_COLOR_FLOOR 0xFFD700FF
# define MINIMAP_COLOR_PLAYER 0xFF1493FF

extern mlx_t		*g_mlx;
extern mlx_image_t	*g_img;
extern t_hookservice	*g_hookservice;

extern struct s_camera
{
	t_vector2	pos;
	t_vector2	dir;
	t_vector2	plane;
}	g_camera;

extern struct s_map
{
	int	width;
	int	height;
	struct s_map_tile
	{
		enum e_tile	tile_type;
		double		opacity;
	} *buffer;
}	g_map;

extern struct s_theme
{
	mlx_texture_t *no;
	mlx_texture_t *so;
	mlx_texture_t *we;
	mlx_texture_t *ea;
	mlx_texture_t *door;
	t_color4 ceiling;
	t_color4 floor;
}					g_theme;

extern struct s_view_model
{
	mlx_image_t *img;
	mlx_instance_t *inst;
	t_ivector2 og_pos;
}	g_view_model;

extern struct s_doors
{
	t_ivector2 *locations;
	int count;
}	g_doors;

#endif
