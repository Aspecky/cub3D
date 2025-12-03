/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:48:29 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/02 18:23:52 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdbool.h>
#include <mlx_aux/Vector2.h>

typedef struct s_raycast_result
{
	bool	hit;
	int		side;
	t_vector2	stepSize;
	t_vector2	sideDist;
	t_vector2	position;
	double distance;
} t_raycast_result;

t_raycast_result raycast(t_vector2 origin, t_vector2 direction, double max_distance);

#endif
