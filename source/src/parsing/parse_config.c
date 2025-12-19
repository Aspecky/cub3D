/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:51:03 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/01 20:49:56 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <string.h>
#include <stdlib.h>

int parse_config_line(char *line, t_parse_data *data)
{
    char *trimmed;
    
    if (!line)
        return (0);
    trimmed = line;
    while (*trimmed == ' ' || *trimmed == '\t')
        trimmed++;
    if (ft_strncmp(trimmed, "NO ", 3) == 0)
        return (parse_texture(trimmed + 3, &data->no_path, &data->no_set));
    else if (ft_strncmp(trimmed, "SO ", 3) == 0)
        return (parse_texture(trimmed + 3, &data->so_path, &data->so_set));
    else if (ft_strncmp(trimmed, "WE ", 3) == 0)
        return (parse_texture(trimmed + 3, &data->we_path, &data->we_set));
    else if (ft_strncmp(trimmed, "EA ", 3) == 0)
        return (parse_texture(trimmed + 3, &data->ea_path, &data->ea_set));
    else if (ft_strncmp(trimmed, "F ", 2) == 0)
        return (parse_color(trimmed + 2, data->floor_rgb, &data->floor_set));
    else if (ft_strncmp(trimmed, "C ", 2) == 0)
        return (parse_color(trimmed + 2, data->ceiling_rgb, &data->ceiling_set));
    
    ft_dprintf(2, "Error\nInvalid configuration line\n");
    return (0);
}

int parse_texture(char *path_str, char **dest, bool *is_set)
{
    char *start;
    char *end;
    int len;

    if (*is_set)
    {
        ft_dprintf(2, "Error\nDuplicate texture definition\n");
        return (0);
    }
    start = path_str;
    while (*start == ' ' || *start == '\t')
        start++;

    end = start;
    while (*end && *end != '\n' && *end != '\r' && 
           *end != ' ' && *end != '\t')
        end++;
    
    len = end - start;
    if (len == 0)
    {
        ft_dprintf(2, "Error\nEmpty texture path\n");
        return (0);
    }
    *dest = malloc(len + 1);
    if (!*dest)
        return (0);
    
    ft_memcpy(*dest, start, len);
    (*dest)[len] = '\0';
    
    *is_set = true;
    return (1);
}

static void free_split(char **split)
{
    int i;
    
    if (!split)
        return;
    
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

static char *trim_whitespace(char *str)
{
    char *end;

    while (ft_isspace(*str))
        str++;
    
    if (*str == 0)
        return (str);

    end = str + ft_strlen(str) - 1;
    while (end > str && ft_isspace(*end))
        end--;
    
    end[1] = '\0';
    
    return (str);
}

int parse_color(char *color_str, int *rgb, bool *is_set)
{
    char **components;
    int i;
    int value;
    char *trimmed;

    if (*is_set)
    {
        ft_dprintf(2, "Error\nDuplicate color definition\n");
        return (0);
    }
    
    trimmed = trim_whitespace(color_str);

    components = ft_split(trimmed, ',');
    if (!components)
    {
        ft_dprintf(2, "Error\nMemory allocation failed\n");
        return (0);
    }

    i = 0;
    while (components[i])
        i++;
    
    if (i != 3)
    {
        ft_dprintf(2, "Error\nInvalid RGB format (need R,G,B)\n");
        free_split(components);
        return (0);
    }
    
    i = 0;
    while (i < 3)
    {
        char *trimmed_comp = trim_whitespace(components[i]);

        value = ft_atoi(trimmed_comp);

        if (value < 0 || value > 255)
        {
            ft_dprintf(2, "Error\nRGB value out of range (0-255): %d\n", value);
            free_split(components);
            return (0);
        }
        
        rgb[i] = value;
        i++;
    }
    
    free_split(components);
    *is_set = true;
    return (1);
}
