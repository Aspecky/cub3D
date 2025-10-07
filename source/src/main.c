/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:16:05 by mtarrih           #+#    #+#             */
/*   Updated: 2025/10/07 16:43:59 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include <mlx42.h>
#include <stdio.h>

int main(void)
{
	mlx_t *mlx;
	int32_t width;
	int32_t height;

	mlx = mlx_init(1, 1, "tmp", 0);
	mlx_get_monitor_size(0, &width, &height);
	mlx_terminate(mlx);
	mlx = mlx_init((width * MONITOR_SCALE) / 100,
				   (height * MONITOR_SCALE) / 100, "cub3D", false);

	mlx_loop(mlx);
	mlx_terminate(mlx);
}
