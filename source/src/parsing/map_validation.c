/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamar <kamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by kamar             #+#    #+#             */
/*   Updated: 2025/12/29 17:57:02 by kamar            ###   ########.fr       */
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

static int	is_valid_pos(t_parsing *data, int x, int y)
{
	if (y < 0 || y >= data->map_height)
		return (0);
	if (x < 0 || x >= (int)ft_strlen(data->map[y]))
		return (0);
	return (1);
}

static int	flood_fill(t_parsing *data, char **visited, int x, int y)
{
	if (!is_valid_pos(data, x, y))
		return (0);
	if (data->map[y][x] == ' ')
		return (0);
	if (data->map[y][x] == '1')
		return (1);
	if (visited[y][x])
		return (1);
	visited[y][x] = 1;
	if (!flood_fill(data, visited, x + 1, y))
		return (0);
	if (!flood_fill(data, visited, x - 1, y))
		return (0);
	if (!flood_fill(data, visited, x, y + 1))
		return (0);
	if (!flood_fill(data, visited, x, y - 1))
		return (0);
	return (1);
}

int	validate_map_closed(t_parsing *data)
{
	char	**visited;
	int		i;
	int		result;

	visited = malloc(sizeof(char *) * data->map_height);
	if (!visited)
		return (0);
	i = 0;
	while (i < data->map_height)
	{
		visited[i] = malloc(data->map_width + 1);
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (0);
		}
		ft_memset(visited[i], 0, data->map_width + 1);
		i++;
	}
	result = flood_fill(data, visited, data->player_pos.x, data->player_pos.y);
	i = 0;
	while (i < data->map_height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
	if (!result)
	{
		dputstr("Error: map is not closed\n", 2);
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
