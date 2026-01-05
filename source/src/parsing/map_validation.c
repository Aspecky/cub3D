/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamar <kamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by kamar             #+#    #+#             */
/*   Updated: 2026/01/05 17:44:55 by kamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D');
}

int	validate_map_line(char *line)
{
	int	i;

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

int	find_player(t_parsing *data)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
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



static char	get_cell(t_parsing *data, int x, int y)
{
	if (y < 0 || y >= data->map_height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(data->map[y]))
		return (' ');
	return (data->map[y][x]);
}

static int	find_first_non_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

static int	find_last_non_space(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && line[i] == ' ')
		i--;
	return (i);
}

int	check_map_borders(t_parsing *data)
{
	int	i;
	int	j;
	int	first_char;
	int	last_char;

	i = 0;
	while (i < data->map_height)
	{
		first_char = find_first_non_space(data->map[i]);
		last_char = find_last_non_space(data->map[i]);
		if (i == 0 || i == data->map_height - 1)
		{
			j = first_char;
			while (j <= last_char)
			{
				if (data->map[i][j] != '1' && data->map[i][j] != ' ')
				{
					dputstr("Error: map must be surrounded by walls\n", 2);
					return (0);
				}
				j++;
			}
		}
		else
		{
			if (first_char >= 0 && data->map[i][first_char] != '1')
			{
				dputstr("Error: map must be surrounded by walls\n", 2);
				return (0);
			}
			if (last_char >= 0 && data->map[i][last_char] != '1')
			{
				dputstr("Error: map must be surrounded by walls\n", 2);
				return (0);
			}
		}
		j = 0;
		while (j < (int)ft_strlen(data->map[i]))
		{
			if (i > 0 && data->map[i][j] != '1' && data->map[i][j] != ' ')
			{
				if (get_cell(data, j, i - 1) == ' ')
				{
					dputstr("Error: map must be surrounded by walls\n", 2);
					return (0);
				}
				if (j > 0 && get_cell(data, j - 1, i - 1) == ' ')
				{
					dputstr("Error: map must be surrounded by walls\n", 2);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}


static int	is_wall(char c)
{
	return (c == '1');
}

static int	is_void(char c)
{
	return (c == ' ');
}

static int	validate_door_horizontal(t_parsing *data, int x, int y)
{
	char	left;
	char	right;
	char	up;
	char	down;

	left = get_cell(data, x - 1, y);
	right = get_cell(data, x + 1, y);
	up = get_cell(data, x, y - 1);
	down = get_cell(data, x, y + 1);
	if (is_void(left) || is_void(right) || is_void(up) || is_void(down))
	{
		dputstr("Error: door 'D' cannot be adjacent to void/space\n", 2);
		return (0);
	}
	if (is_wall(left) && is_wall(right) && !is_wall(up) && !is_wall(down))
		return (1);
	return (0);
}

static int	validate_door_vertical(t_parsing *data, int x, int y)
{
	char	left;
	char	right;
	char	up;
	char	down;

	left = get_cell(data, x - 1, y);
	right = get_cell(data, x + 1, y);
	up = get_cell(data, x, y - 1);
	down = get_cell(data, x, y + 1);
	if (is_void(left) || is_void(right) || is_void(up) || is_void(down))
	{
		dputstr("Error: door 'D' cannot be adjacent to void/space\n", 2);
		return (0);
	}
	if (is_wall(up) && is_wall(down) && !is_wall(left) && !is_wall(right))
		return (1);
	return (0);
}

static int	validate_single_door(t_parsing *data, int x, int y)
{
	if (validate_door_horizontal(data, x, y))
		return (1);
	if (validate_door_vertical(data, x, y))
		return (1);
	dputstr("Error: door 'D' must be between two walls (horizontal or vertical)\n", 2);
	return (0);
}

int	validate_doors(t_parsing *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'D')
			{
				if (!validate_single_door(data, j, i))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
