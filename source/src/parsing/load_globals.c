/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_globals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:23:39 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/01 20:25:23 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <MLX42/MLX42.h>
#include <stdio.h>
#include "consts.h"

static unsigned int create_color(int r, int g, int b, int a)
{
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

int load_into_globals(t_parse_data *data)
{
    g_theme.no = mlx_load_png(data->no_path);
    if (!g_theme.no)
    {
        printf("Error\nFailed to load texture: %s\n", data->no_path);
        return (0);
    }
    
    g_theme.so = mlx_load_png(data->so_path);
    g_theme.we = mlx_load_png(data->we_path);
    g_theme.ea = mlx_load_png(data->ea_path);
    if (!g_theme.so || !g_theme.we || !g_theme.ea)
    {
        printf("Error\nFailed to load texture(s)\n");
        return (0);
    }
    g_theme.floor = create_color(data->floor_rgb[0], 
                                  data->floor_rgb[1], 
                                  data->floor_rgb[2], 
                                  255);
    g_theme.ceiling = create_color(data->ceiling_rgb[0], 
                                    data->ceiling_rgb[1], 
                                    data->ceiling_rgb[2], 
                                    255);
    if (!load_map(data))
        return (0);
    if (!load_camera(data))
        return (0);
    
    return (1);
}