/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamar <kamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 18:02:46 by kamar             #+#    #+#             */
/*   Updated: 2025/12/26 16:59:59 by kamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "ftlibc/ft_stdlib.h"
#include "ftlibc/ft_stdio.h"
#include "ftlibc/ft_string.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void init_parse(t_parsing *data)
{
    ft_memset(data, 0, sizeof(t_parsing));

    data->no_path = NULL;
    data->ea_path = NULL;
    data->so_path = NULL;
    data->we_path = NULL;

    data->floor.r = -1;
    data->floor.g = -1;
    data->floor.b = -1;
    data->floor.alpha = 255;

    data->ceiling.r = -1;
    data->ceiling.g = -1;
    data->ceiling.b = -1;
    data->ceiling.alpha = 255;

    data->map = NULL;
    data->map_height = 0;
    data->map_width = 0;

}

int valid_cub(char *file)
{
    int len;

    if (!file)
        return 0;
    len = ft_strlen(file);

    if (len < 5)
        return 0;

    if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
        return 0;
    return 1;
}

void free_parse(t_parsing *data)
{
    int i;

    if (data->no_path)
        free(data->no_path);
    if (data->so_path)
        free(data->so_path);
    if (data->ea_path)
        free (data->ea_path);
    if (data->we_path)
        free(data->we_path);

    if (data->map)
    {
        i = 0;
        while (i < data->map_height)
        {
            if (data->map[i])
            {
                free(data->map[i]);
            }
            i++;
        }
        free(data->map);
    }
}

int is_empty_line(char *line)
{
    int i;

    if (!line)
        return 1;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r')
            return 0;
        i++;
    }
    return 1;
}

int parse_texture(char *path_str, char **dest)
{
    char *start;
    char *end;
    int len;

    start = path_str;
    while (*start == ' ' || *start == '\t')
        start++;
    end = start;
    while (*end && *end != '\n' && *end != '\r' && *end != ' ' && *end != '\t')
        end++;

    len = end - start;
    if (len == 0)
    {
        dputstr("Error, empty texture path\n", 2);
        return 0;
    }

    *dest = malloc(len + 1);
    if (!dest)
        return 0;
    ft_memcpy(*dest, start, len);
    (*dest)[len] = '\0';

    return (1);
}

int parse_color(char *color_str, t_color_rgb *color)
{
    char *start;
    int values[3];
    int i;

    start = color_str;
    while (*start == ' ' || *start == '\t')
        start++;

    i = 0;
    while (i < 3)
    {
        if (!*start || (*start != '-' && (*start < '0' || *start > '9')))
        {
            dputstr("Error: invalid color format\n", 2);
            return (0);
        }
        values[i] = ft_atoi(start);
        if (values[i] < 0 || values[i] > 255)
        {
            dputstr("Error: color value must be between 0 and 255\n", 2);
            return (0);
        }
        while (*start && *start != ',' && *start != ' ' && *start != '\t' && *start != '\n')
            start++;
        if (i < 2)
        {
            if (*start != ',')
            {
                dputstr("Error: color values must be separated by commas\n", 2);
                return (0);
            }
            start++;
        }
        i++;
    }
    color->r = (uint8_t)values[0];
    color->g = (uint8_t)values[1];
    color->b = (uint8_t)values[2];
    color->alpha = 255;
    return (1);
}

int parse_line(char *line, t_parsing *data)
{
   char *trimmed;
   
    if (!line)
        return 0;

    trimmed = line;
    while (*trimmed == ' ' || *trimmed == '\t')
        trimmed++;

    if (ft_strncmp(trimmed, "NO ", 3) == 0)
        return (parse_texture(trimmed + 3, &data->no_path));
    else if (ft_strncmp(trimmed, "SO ", 3) == 0)
        return (parse_texture(trimmed + 3, &data->so_path));
    else if (ft_strncmp(trimmed, "WE ", 3) == 0)
        return (parse_texture(trimmed + 3, &data->we_path));
    else if (ft_strncmp(trimmed, "EA ", 3) == 0)
        return (parse_texture(trimmed + 3, &data->ea_path));
    else if (ft_strncmp(trimmed, "F ", 2) == 0)
        return (parse_color(trimmed + 2, &data->floor));
    else if (ft_strncmp(trimmed, "C ", 2) == 0)
        return (parse_color(trimmed + 2, &data->ceiling));

    dputstr("Error\n invalid config line", 2);
    return (0);
}

static int is_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || 
            c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D');
}

static int find_player(t_parsing *data)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = 0;
    while (i < data->map_height)
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
                data->map[i][j] == 'E' || data->map[i][j] == 'W')
            {
                data->player_dir = data->map[i][j];
                data->player_pos.x = j;
                data->player_pos.y = i;
                player_count++;
            }
            j++;
        }
        i++;
    }
    if (player_count != 1)
    {
        dputstr("Error: map must have exactly one player\n", 2);
        return (0);
    }
    return (1);
}

static int validate_map_line(char *line)
{
    int i;

    i = 0;
    while (line[i] && line[i] != '\n')
    {
        if (!is_map_char(line[i]))
        {
            dputstr("Error: invalid character in map\n", 2);
            return (0);
        }
        i++;
    }
    return (1);
}

int parse_map(int fd, t_lninfo *lninfo, t_parsing *data)
{
    ssize_t ret;
    int len;

    ret = dgetline(fd, lninfo);
    while (ret > 0 && is_empty_line(lninfo->line))
        ret = dgetline(fd, lninfo);
    
    if (ret <= 0)
    {
        dputstr("Error: no map found\n", 2);
        return (0);
    }

    data->map_height = 0;
    data->map = malloc(sizeof(char *) * 1000);
    if (!data->map)
        return (0);

    while (ret > 0)
    {
        if (is_empty_line(lninfo->line))
            break;
        if (!validate_map_line(lninfo->line))
        {
            return (0);
        }
        len = ft_strlen(lninfo->line);
        if (len > 0 && lninfo->line[len - 1] == '\n')
            len--;
        data->map[data->map_height] = malloc(len + 1);
        if (!data->map[data->map_height])
            return (0);
        ft_memcpy(data->map[data->map_height], lninfo->line, len);
        data->map[data->map_height][len] = '\0';
        
        if (len > data->map_width)
            data->map_width = len;
        data->map_height++;
        ret = dgetline(fd, lninfo);
    }

    if (data->map_height == 0)
    {
        dputstr("Error: empty map\n", 2);
        return (0);
    }

    if (!find_player(data))
        return (0);

    return (1);
}
int parse_content(int fd, t_parsing *data)
{
    t_lninfo lninfo;
    ssize_t ret;
    int config_count;

    ft_memset(&lninfo, 0, sizeof(t_lninfo));
    lninfo.store = NULL;
    lninfo._store_size = 0;
    lninfo.line = NULL;
    lninfo.line_size = 0;

    config_count = 0;
    while(config_count < 6)
    {
        ret = dgetline(fd, &lninfo);

        if (ret == -1 || ret == 0)
        {
            dputstr("Error\n", 2);
            free(lninfo.line);
            free(lninfo.store);
            return (0);
        }

        if (is_empty_line(lninfo.line))
            continue ;
        if (parse_line(lninfo.line, data))
            config_count++;
        else 
        {
            free (lninfo.line);
            free(lninfo.store);
            return (0);
        }
    }
    if (!parse_map(fd, &lninfo, data))
    {
        free(lninfo.line);
        free(lninfo.store);
        return (0);
    }
    free(lninfo.line);
    free(lninfo.store);
    return (1);
}
int     parse_file(char *file)
{
    t_parsing data;
    int fd;

    if (!valid_cub(file))
    {
        dputstr("Error, invalid file extension\n, must be .cub\n", 2);
        return (0);
    }

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("Error, cannot open file %s\n", file);
        return (0);
    }
    init_parse(&data);
    if(!parse_content(fd, &data))
    {
        close(fd);
        free_parse(&data);
        return (0);
    }
    close(fd);
    return (1);
}

