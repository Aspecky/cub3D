/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:26:42 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/27 19:52:08 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "init.h"
#include "textures.h"
#include <mlx_aux/mlx_aux.h>

bool init_textures(t_parsing parse)
{
	g_theme.no = mlx_load_png(parse.no_path);
	g_theme.ea = mlx_load_png(parse.ea_path);
	g_theme.so = mlx_load_png(parse.so_path);
	g_theme.we = mlx_load_png(parse.we_path);
	g_theme.door = mlx_load_png("assets/door.png");
	g_theme.ceiling = color4_from_rgb(parse.ceiling);
	g_theme.floor = color4_from_rgb(parse.floor);
	if (!(g_theme.no && g_theme.ea && g_theme.so && g_theme.we))
		return (false);
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
