/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 21:00:33 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 17:27:41 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

#include <MLX42/MLX42.h>

# define MINIMAP_OFFSET 0.01
# define MINIMAP_CONTENT_SCALE 0.82
# define MINIMAP_OFFSET_X 0.007
# define MINIMAP_OFFSET_Y -0.01

bool init_minimap(void);
void minimap_bind(void *param);

#endif
