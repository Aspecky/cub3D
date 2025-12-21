/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:56:27 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 17:31:57 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADERS_H
# define LOADERS_H

# include "mlx_aux/Vector2.h"
# include <stdbool.h>

bool	load_player(t_vector2 position, t_vector2 direction);
bool	load_minimap(void);
bool	load_fps_counter(void);

#endif
