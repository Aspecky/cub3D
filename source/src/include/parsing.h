/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 17:56:26 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/15 22:40:05 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <stdio.h>
# include "consts.h"
# include "ftlibc/ft_stdio.h"  
# include <fcntl.h>
# include <stdbool.h>
#include "ftlibc/ft_string.h"
#include "ftlibc/ft_ctype.h"
#include "ftlibc/ft_math.h"
#include "ftlibc/ft_stdint.h"
#include "ftlibc/ft_stdlib.h"
#include "ftlibc/Vector.h"
#include "ftlibc/SinglyLinkedList.h"
#include "ftlibc/SinglyLinkedNode.h"

typedef struct s_parse_data {
    char    *no_path;
    char    *so_path;
    char    *we_path;
    char    *ea_path;
    int     floor_rgb[3];
    int     ceiling_rgb[3];
    char    **map_lines;
    int     map_line_count;
    bool    no_set;
    bool    so_set;
    bool    we_set;
    bool    ea_set;
    bool    floor_set;
    bool    ceiling_set;
} t_parse_data;

int     validate_walls(t_parse_data *data);
int     parse_file(char *filename);

void    init_parse_data(t_parse_data *data);
void    free_parse_data(t_parse_data *data);
int     validate_extension(char *filename);
int     parse_content(int fd, t_parse_data *data);
int     is_empty_line(char *line);
int     parse_config_line(char *line, t_parse_data *data);
int		validate_walls(t_parse_data *data);
int		validate_walls_sides(t_parse_data *data);
void ft_dprintf(int fd, const char *format, ...);
int parse_config_line(char *line, t_parse_data *data);
int parse_texture(char *path_str, char **dest, bool *is_set);
int parse_color(char *color_str, int *rgb, bool *is_set);
int load_map(t_parse_data *data);
void set_camera_direction(char dir);
int load_camera(t_parse_data *data);
int load_into_globals(t_parse_data *data);
int validate_data(t_parse_data *data);
int parse_map(int fd, t_lninfo *lninfo, t_parse_data *data);
int file_exists(char *path);
int validate_map(t_parse_data *data);
int validate_map_characters(t_parse_data *data);
int validate_player(t_parse_data *data);
#endif