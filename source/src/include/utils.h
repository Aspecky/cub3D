/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:48:29 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/23 16:58:54 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <MLX42/MLX42.h>
# include "raycast.h"

mlx_texture_t		*tile_type_to_texture(t_raycast_result ray,
						t_vector2 direction);

#endif
