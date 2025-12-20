/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window_bind.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:46:15 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 17:38:00 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binds.h"
#include "consts.h"

void	close_window_bind(mlx_key_data_t keydata, void *param)
{
	(void)param;
	if (keydata.action == MLX_PRESS)
		mlx_close_window(g_mlx);
}
