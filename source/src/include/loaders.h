/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:56:27 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/12 20:47:47 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADERS_H
# define LOADERS_H

#include <stdbool.h>
#include "mlx_aux/Vector2.h"

bool load_camera(t_vector2 position, t_vector2 direction);
bool load_minimap(void);

#endif
