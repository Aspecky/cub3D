/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:49:20 by mtarrih           #+#    #+#             */
/*   Updated: 2025/11/30 18:29:57 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGS_H
# define BINDINGS_H

#include <MLX42/MLX42.h>

void	close_window_bind(mlx_key_data_t keydata, void *param);
void	movement_bind(void *param);
void	cursor_hook(double xpos, double ypos, void* param);
void	head_bobbing_bind(void *param);

#endif
