/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:26:23 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 15:34:16 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "mlx_aux/Vector2.h"

bool	init_camera(t_vector2 position, t_vector2 direction);
bool	init_minimap(void);
bool	init_textures(void);

#endif
