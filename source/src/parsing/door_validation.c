/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:17:19 by kaneddam          #+#    #+#             */
/*   Updated: 2026/01/06 18:27:15 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	get_cell(t_parsing *data, int x, int y)
{
	if (y < 0 || y >= data->map_height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(data->map[y]))
		return (' ');
	return (data->map[y][x]);
}

int	validate_door_horizontal(t_parsing *data, int x, int y)
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
		dputstr("Error: door 'D' cannot be adjacent to void\n", 2);
		return (0);
	}
	if (is_wall(left) && is_wall(right) && !is_wall(up) && !is_wall(down))
		return (1);
	return (0);
}

int	validate_door_vertical(t_parsing *data, int x, int y)
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
		dputstr("Error: door 'D' cannot be adjacent to void\n", 2);
		return (0);
	}
	if (is_wall(up) && is_wall(down) && !is_wall(left) && !is_wall(right))
		return (1);
	return (0);
}

int	validate_single_door(t_parsing *data, int x, int y)
{
	if (validate_door_horizontal(data, x, y))
		return (1);
	if (validate_door_vertical(data, x, y))
		return (1);
	dputstr("Error: door 'D' must be between two walls\n", 2);
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
