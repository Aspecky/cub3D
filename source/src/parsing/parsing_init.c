/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:53:08 by kaneddam          #+#    #+#             */
/*   Updated: 2025/11/30 18:53:22 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void init_parse_data(t_parse_data *data)
{
    ft_memset(data, 0, sizeof(t_parse_data));
    
    data->no_path = NULL;
    data->so_path = NULL;
    data->we_path = NULL;
    data->ea_path = NULL;
    
    data->floor_rgb[0] = -1;
    data->floor_rgb[1] = -1;
    data->floor_rgb[2] = -1;
    
    data->ceiling_rgb[0] = -1;
    data->ceiling_rgb[1] = -1;
    data->ceiling_rgb[2] = -1;
    
    data->map_lines = NULL;
    data->map_line_count = 0;
    
    data->no_set = false;
    data->so_set = false;
    data->we_set = false;
    data->ea_set = false;
    data->floor_set = false;
    data->ceiling_set = false;
}

void free_parse_data(t_parse_data *data)
{
    int i;
    
    if (data->no_path)
        free(data->no_path);
    if (data->so_path)
        free(data->so_path);
    if (data->we_path)
        free(data->we_path);
    if (data->ea_path)
        free(data->ea_path);
    
    if (data->map_lines)
    {
        i = 0;
        while (i < data->map_line_count)
        {
            if (data->map_lines[i])
                free(data->map_lines[i]);
            i++;
        }
        free(data->map_lines);
    }
}