/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:48:29 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/21 22:32:48 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <MLX42/MLX42.h>
# include <mlx_aux/Vector2.h>
# include <stdbool.h>

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
mlx_texture_t		*tile_type_to_texture(t_raycast_result ray,
						t_vector2 direction);

#endif
