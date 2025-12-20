/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:21:24 by kaneddam          #+#    #+#             */
/*   Updated: 2025/11/30 20:23:23 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int validate_data(t_parse_data *data)
{
    if (!data->no_set || !data->so_set || 
        !data->we_set || !data->ea_set)
    {
        printf("Error\nMissing texture(s)\n");
        return (0);
    }
    
    if (!data->floor_set || !data->ceiling_set)
    {
        printf("Error\nMissing color(s)\n");
        return (0);
    }
    
    if (!file_exists(data->no_path))
    {
        printf("Error\nTexture file not found: %s\n", data->no_path);
        return (0);
    }

    if (!validate_map(data))
        return (0);
    
    return (1);
}

int file_exists(char *path)
{
    int fd;
    
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    
    close(fd);
    return (1);
}

int validate_map(t_parse_data *data)
{
    if (!validate_map_characters(data))
        return (0);
    if (!validate_player(data))
        return (0);
    if (!validate_walls(data))
        return (0);
    
    return (1);
}

int validate_map_characters(t_parse_data *data)
{
    int i;
    int j;
    char c;
    
    i = 0;
    while (i < data->map_line_count)
    {
        j = 0;
        while (data->map_lines[i][j])
        {
            c = data->map_lines[i][j];
            if (c != '0' && c != '1' && c != ' ' &&
                c != 'N' && c != 'S' && c != 'E' && c != 'W')
            {
                printf("Error\nInvalid character in map: '%c'\n", c);
                return (0);
            }
            j++;
        }
        i++;
    }
    
    return (1);
}

int validate_player(t_parse_data *data)
{
    int i;
    int j;
    int count;
    char c;
    
    count = 0;
    i = 0;
    while (i < data->map_line_count)
    {
        j = 0;
        while (data->map_lines[i][j])
        {
            c = data->map_lines[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
                count++;
            j++;
        }
        i++;
    }
    
    if (count == 0)
    {
        printf("Error\nNo player found in map\n");
        return (0);
    }
    if (count > 1)
    {
        printf("Error\nMultiple players found in map\n");
        return (0);
    }
    return (1);
}
