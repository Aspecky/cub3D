/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:26:42 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 15:34:14 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "init.h"
#include "textures.h"
#include <mlx_aux/mlx_aux.h>

bool init_textures(void)
{
	g_theme.no = mlx_load_png("assets/North.png");
	g_theme.ea = mlx_load_png("assets/East.png");
	g_theme.so = mlx_load_png("assets/South.png");
	g_theme.we = mlx_load_png("assets/West.png");
	g_theme.door = mlx_load_png("assets/door.png");
	g_theme.ceiling = color4_from_hex("87CEEB");
	g_theme.floor = color4_from_hex("9B7653");
	mlx_resize_texture(g_mlx, g_theme.no, 64, 64);
	mlx_resize_texture(g_mlx, g_theme.ea, 64, 64);
	mlx_resize_texture(g_mlx, g_theme.so, 64, 64);
	mlx_resize_texture(g_mlx, g_theme.we, 64, 64);
	transpose_texture(g_theme.no);
	transpose_texture(g_theme.ea);
	transpose_texture(g_theme.so);
	transpose_texture(g_theme.we);
	transpose_texture(g_theme.door);
	return (true);
}
