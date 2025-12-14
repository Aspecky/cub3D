/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:27:11 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/14 17:27:50 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"

static void	swap_pixels(uint8_t *a, uint8_t *b)
{
	uint8_t	tmp[4];

	tmp[0] = a[0];
	tmp[1] = a[1];
	tmp[2] = a[2];
	tmp[3] = a[3];
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
	a[3] = b[3];
	b[0] = tmp[0];
	b[1] = tmp[1];
	b[2] = tmp[2];
	b[3] = tmp[3];
}

void	transpose_texture(mlx_texture_t *tex)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	size;
	uint8_t		*pixels;

	size = tex->width;
	pixels = tex->pixels;
	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < x)
		{
			swap_pixels(pixels + (size * y + x) * 4,
				pixels + (size * x + y) * 4);
			y++;
		}
		x++;
	}
}
