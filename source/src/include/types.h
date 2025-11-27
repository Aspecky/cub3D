/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 20:06:57 by mtarrih           #+#    #+#             */
/*   Updated: 2025/11/21 18:29:07 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#include <mlx42.h>
#include <Vector2.h>

typedef struct s_player {
	t_vector2 pos;
	t_vector2 dir;
	t_vector2 plane;
} t_player;

typedef struct s_env {
	t_player player;
} t_env;

#endif
