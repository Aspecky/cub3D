/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter_bind.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 21:39:42 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 17:38:00 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binds.h"
#include "consts.h"
#include <MLX42/MLX42.h>

static char	*int_to_str(int n, char *str, size_t size)
{
	size_t	i;

	i = size - 1;
	str[i] = '\0';
	if (n == 0)
	{
		str[--i] = '0';
		return (str + i);
	}
	while (n > 0 && i > 0)
	{
		str[--i] = (char)('0' + (n % 10));
		n /= 10;
	}
	return (str + i);
}

void	fps_counter_bind(void *param)
{
	static mlx_image_t	*fps_text = NULL;
	int					fps;
	char				fps_str[5];
	char				*fps_ptr;

	(void)param;
	if (g_mlx->delta_time > 0)
		fps = (int)(1.0 / g_mlx->delta_time);
	else
		fps = 0;
	fps_ptr = int_to_str(fps, fps_str, sizeof(fps_str));
	if (fps_text)
		mlx_delete_image(g_mlx, fps_text);
	fps_text = mlx_put_string(g_mlx, fps_ptr, g_mlx->width - 50, 10);
}
