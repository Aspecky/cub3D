/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 15:26:23 by mtarrih           #+#    #+#             */
/*   Updated: 2026/01/03 18:35:08 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "mlx_aux/Vector2.h"
# include "parsing.h"

bool	init_textures(t_parsing parse);
bool	init_map(t_parsing parse);

#endif
