/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:50:08 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/01 18:28:51 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <string.h>

static char *strdup_line(char *line)
{
    int len;
    char *dup;
    
    if (!line)
        return (NULL);
    
    len = ft_strlen(line);
    
    if (len > 0 && line[len - 1] == '\n')
        len--;
    if (len > 0 && line[len - 1] == '\r')
        len--;
    
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    
    ft_memcpy(dup, line, len);
    dup[len] = '\0';
    
    return (dup);
}

static char **realloc_map_lines(char **old, int old_size, int new_size)
{
    char **new;
    int i;
    
    new = malloc(sizeof(char *) * new_size);
    if (!new)
        return (NULL);
    
    i = 0;
    while (i < old_size)
    {
        new[i] = old[i];
        i++;
    }
    
    free(old);
    return (new);
}

int parse_map(int fd, t_lninfo *lninfo, t_parse_data *data)
{
    ssize_t ret;
    char *line_copy;
    int capacity;
    char **temp;
    
    capacity = 10;
    data->map_lines = malloc(sizeof(char *) * capacity);
    if (!data->map_lines)
        return (0);
    
    data->map_line_count = 0;
    
    while (1)
    {
        ret = dgetline(fd, lninfo);
        
        if (ret == -1)
        {
            ft_dprintf(2, "Error\nRead error while parsing map\n");
            return (0);
        }
        
        if (ret == 0)
            break;
        if (data->map_line_count == 0 && is_empty_line(lninfo->line))
            continue;

        if (data->map_line_count > 0 && is_empty_line(lninfo->line))
            break;

        if (data->map_line_count >= capacity)
        {
            capacity *= 2;
            temp = realloc_map_lines(data->map_lines, 
                                     data->map_line_count, 
                                     capacity);
            if (!temp)
                return (0);
            data->map_lines = temp;
        }

        line_copy = strdup_line(lninfo->line);
        if (!line_copy)
            return (0);
        
        data->map_lines[data->map_line_count] = line_copy;
        data->map_line_count++;
    }
    
    if (data->map_line_count == 0)
    {
        ft_dprintf(2, "Error\nNo map found\n");
        return (0);
    }
    
    return (1);
}
