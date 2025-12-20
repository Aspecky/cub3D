/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:27:38 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/01 20:33:02 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <string.h>
#include "consts.h"

int load_map(t_parse_data *data)
{
    int max_width;
    int i;
    int j;
    
    max_width = 0;
    i = 0;
    while (i < data->map_line_count)
    {
        int len = ft_strlen(data->map_lines[i]);
        if (len > max_width)
            max_width = len;
        i++;
    }
    
    g_map.width = max_width;
    g_map.height = data->map_line_count;
    
    g_map.buffer = malloc(sizeof(struct s_map_tile) * g_map.width * g_map.height);
    if (!g_map.buffer)
        return (0);
    
    i = 0;
    while (i < g_map.height)
    {
        j = 0;
        while (j < g_map.width)
        {
            char c;
         
            if (j < (int)strlen(data->map_lines[i]))
                c = data->map_lines[i][j];
            else
                c = ' ';
            if (c == '1')
            {
                g_map.buffer[i * g_map.width + j].tile_type = 1;
                g_map.buffer[i * g_map.width + j].opacity = 1.0;
            }
            else if (c == '0' || c == 'N' || c == 'S' || 
                     c == 'E' || c == 'W')
            {
                g_map.buffer[i * g_map.width + j].tile_type = 0;
                g_map.buffer[i * g_map.width + j].opacity = 1.0;
            }
            else
            {
                g_map.buffer[i * g_map.width + j].tile_type = -1;
                g_map.buffer[i * g_map.width + j].opacity = 1.0;
            }
            
            j++;
        }
        i++;
    }
    
    return (1);
}
