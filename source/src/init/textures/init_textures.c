/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:26:42 by mtarrih           #+#    #+#             */
/*   Updated: 2026/01/11 20:07:57 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "consts.h"
#include "init.h"
#include "textures.h"
#include <math.h>
#include <mlx_aux/mlx_aux.h>
#include <stdint.h>

static mlx_texture_t	*load_texture(const char *path)
{
	mlx_texture_t	*tex;
	uint32_t		len;

	tex = mlx_load_png(path);
	if (!tex)
		return (0);
	if (tex->width != tex->height)
	{
		len = (uint32_t)fmin(tex->width, tex->height);
		if (!mlx_resize_texture(g_mlx, tex, len, len))
		{
			mlx_delete_texture(tex);
			return (0);
		}
	}
	return (tex);
}

bool	init_textures(t_parsing parse)
{
	g_theme.no = load_texture(parse.no_path);
	g_theme.ea = load_texture(parse.ea_path);
	g_theme.so = load_texture(parse.so_path);
	g_theme.we = load_texture(parse.we_path);
	g_theme.door = load_texture("assets/textures/door.png");
	g_theme.ceiling = color4_from_rgb(parse.ceiling);
	g_theme.floor = color4_from_rgb(parse.floor);
	if (!(g_theme.no && g_theme.ea && g_theme.so && g_theme.we && g_theme.door))
		return (false);
	transpose_texture(g_theme.no);
	transpose_texture(g_theme.ea);
	transpose_texture(g_theme.so);
	transpose_texture(g_theme.we);
	transpose_texture(g_theme.door);
	return (true);
}
