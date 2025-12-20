/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:49:20 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 17:28:10 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGS_H
# define BINDINGS_H

#include <MLX42/MLX42.h>

void	close_window_bind(mlx_key_data_t keydata, void *param);
void	automatic_doors_bind(void *param);
void	fps_counter_bind(void *param);

#endif
