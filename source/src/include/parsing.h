/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:34:13 by kamar             #+#    #+#             */
/*   Updated: 2026/01/06 18:18:44 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "mlx_aux/Color4.h"
# include "mlx_aux/Vector2.h"
# include "ftlibc/ft_stdio.h"
#include <stdbool.h>
#include "ftlibc/ft_stdio.h"
#include "ftlibc/ft_string.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "ftlibc/ft_stdlib.h"
#include "ftlibc/ft_ctype.h"


/*
   111111
   100001
  100000001
    10001
    11111
*/
typedef struct s_parsing
{
    char *no_path;
    char *ea_path;
    char *so_path;
    char *we_path;
    t_color_rgb floor;
    t_color_rgb ceiling;
    char **map;
    int map_width;
    int map_height;
    char player_dir;
    t_ivector2 player_pos;
    bool ok;
} t_parsing;

void *ft_realloc(void *ptr, size_t old_size, size_t new_size);
void init_parse(t_parsing *data);
void free_parse(t_parsing *data);
int valid_cub(char *file);
int is_empty_line(char *line);
int parse_texture(char *path_str, char **dest);
int parse_color(char *color_str, t_color_rgb *color);
int validate_map_line(char *line);
int find_player(t_parsing *data);
int	is_void(char c);
int	is_wall(char c);
int	is_map_char(char c);
char	get_cell(t_parsing *data, int x, int y);
int check_map_borders(t_parsing *data);
int validate_doors(t_parsing *data);
int	validate_single_door(t_parsing *data, int x, int y);
int	validate_door_vertical(t_parsing *data, int x, int y);
int	validate_door_horizontal(t_parsing *data, int x, int y);
int parse_line(char *line, t_parsing *data);
int parse_map(int fd, t_lninfo *lninfo, t_parsing *data);
int parse_content(int fd, t_parsing *data);
t_parsing parse_file(char *file);

int	check_side_borders(t_parsing *data, int i, int first, int last);
int	check_top_bottom_borders(t_parsing *data, int i, int first, int last);

int	find_last_non_space(char *line);
int	find_first_non_space(char *line);
int	check_space_leaks(t_parsing *data, int i, int j);

#endif
