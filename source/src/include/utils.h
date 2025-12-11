/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:48:29 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/10 21:54:20 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdbool.h>
#include <mlx_aux/Vector2.h>
#include <MLX42/MLX42.h>
#include "types.h"

void	transpose_texture(mlx_texture_t *tex);

typedef struct s_raycast_result
{
	bool	hit;
	int		side;
	t_vector2	stepSize;
	t_vector2	sideDist;
	double distance;
	t_vector2	position;
	enum e_tile	tile_type;
	double	tile_opacity;
} t_raycast_result;

t_raycast_result raycast(t_vector2 origin, t_vector2 direction, double distance);

#endif
