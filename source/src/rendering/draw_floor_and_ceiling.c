/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceiling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 21:37:25 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/24 21:50:09 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include <stdint.h>

void	draw_floor_and_ceiling(void)
{
	uint32_t	i;
	uint32_t	ceil_end;
	uint32_t	total_size;
	uint32_t	*pixels;
	uint32_t	ceil_color;
	uint32_t	floor_color;

	pixels = (uint32_t *)g_img->pixels;
	ceil_end = g_img->width * (g_img->height / 2 + g_player.pitch);
	total_size = g_img->width * g_img->height;
	ceil_color = ((g_theme.ceiling >> 24) & 0xFF)
		| ((g_theme.ceiling >> 8) & 0xFF00)
		| ((g_theme.ceiling << 8) & 0xFF0000) | 0xFF000000;
	floor_color = ((g_theme.floor >> 24) & 0xFF)
		| ((g_theme.floor >> 8) & 0xFF00)
		| ((g_theme.floor << 8) & 0xFF0000) | 0xFF000000;
	i = 0;
	while (i < ceil_end && i < total_size)
		pixels[i++] = ceil_color;
	while (i < total_size)
		pixels[i++] = floor_color;
}
