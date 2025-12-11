/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 21:00:33 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/11 22:31:50 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

#include <MLX42/MLX42.h>
#include "mlx_aux/Vector2.h"

# define MINIMAP_OFFSET 0.01
# define MINIMAP_CONTENT_SCALE 0.82 // Scale of minimap content relative to frame (adjust to eyeball)
# define MINIMAP_OFFSET_X 0.007 // Additional X offset for centering within imperfect frame (adjust to eyeball)
# define MINIMAP_OFFSET_Y -0.01 // Additional Y offset for centering within imperfect frame (adjust to eyeball)

extern struct s_minimap
{
	mlx_image_t	*img;
	int			tile_size;
	int			tiles_visible;
	int			radius;
	t_ivector2	center;
}	g_minimap;

void minimap_bind(void *param);

#endif
