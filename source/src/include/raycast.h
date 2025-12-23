/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:57:30 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/23 16:59:18 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "mlx_aux/Vector2.h"
# include "types.h"

typedef struct s_dda_init
{
	t_vector2		origin;
	t_vector2		direction;
	t_ivector2		map_pos;
	t_vector2		step_size;
}					t_dda_init;

typedef struct s_raycast_result
{
	bool			hit;
	int				side;
	t_vector2		step_size;
	t_vector2		side_dist;
	double			distance;
	t_vector2		position;
	enum e_tile		tile_type;
	double			tile_opacity;
}					t_raycast_result;

t_raycast_result	raycast(t_vector2 origin, t_vector2 direction,
		double distance);

#endif
