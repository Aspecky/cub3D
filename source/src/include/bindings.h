/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bindings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:49:20 by mtarrih           #+#    #+#             */
/*   Updated: 2025/11/17 20:04:37 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGS_H
# define BINDINGS_H

#include <mlx42.h>

void	close_window_bind(mlx_key_data_t keydata, void *param);
void	movement_bind(void *param);

#endif
