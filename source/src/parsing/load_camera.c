/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:28:13 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/01 18:30:03 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <math.h>


void set_camera_direction(char dir)
{
    if (dir == 'N')
    {
        g_camera.dir.x = 0;
        g_camera.dir.y = -1;
    }
    else if (dir == 'S')
    {
        g_camera.dir.x = 0;
        g_camera.dir.y = 1;
    }
    else if (dir == 'E')
    {
        g_camera.dir.x = 1;
        g_camera.dir.y = 0;
    }
    else if (dir == 'W')
    {
        g_camera.dir.x = -1;
        g_camera.dir.y = 0;
    }
    if (dir == 'N')
    {
        g_camera.plane.x = 0.66;
        g_camera.plane.y = 0;
    }
    else if (dir == 'S')
    {
        g_camera.plane.x = -0.66;
        g_camera.plane.y = 0;
    }
    else if (dir == 'E')
    {
        g_camera.plane.x = 0;
        g_camera.plane.y = 0.66;
    }
    else if (dir == 'W')
    {
        g_camera.plane.x = 0;
        g_camera.plane.y = -0.66;
    }
}


int load_camera(t_parse_data *data)
{
    int i, j;
    char dir;
    
    i = 0;
    while (i < data->map_line_count)
    {
        j = 0;
        while (data->map_lines[i][j])
        {
            dir = data->map_lines[i][j];
            if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
            {
                g_camera.pos.x = j + 0.5;
                g_camera.pos.y = i + 0.5;
                set_camera_direction(dir);
                
                return (1);
            }
            j++;
        }
        i++;
    }
    
    return (0);
}
