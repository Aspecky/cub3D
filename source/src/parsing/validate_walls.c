/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 22:33:25 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/15 22:39:38 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"
#include <unistd.h>

static int	check_internal_walls(t_parse_data *data);
static int	is_exposed_to_void(t_parse_data *data, int y, int x);

int	validate_walls(t_parse_data *data)
{
	int	i;
	int	last_row;

	last_row = data->map_line_count - 1;
	i = 0;
	while (data->map_lines[0][i])
	{
		if (data->map_lines[0][i] != '1' && data->map_lines[0][i] != ' ')
		{
			ft_dprintf(2, "Error\nMap not closed (top)\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (data->map_lines[last_row][i])
	{
		if (data->map_lines[last_row][i] != '1' && 
			data->map_lines[last_row][i] != ' ')
		{
			ft_dprintf(2, "Error\nMap not closed (bottom)\n");
			return (0);
		}
		i++;
	}
	return (validate_walls_sides(data));
}

int	validate_walls_sides(t_parse_data *data)
{
	int	i;
	int	len;

	i = 0;
	while (i < data->map_line_count)
	{
		if (data->map_lines[i][0] != '1' && data->map_lines[i][0] != ' ')
		{
			ft_dprintf(2, "Error\nMap not closed (left)\n");
			return (0);
		}
		len = ft_strlen(data->map_lines[i]);
		if (len > 0)
		{
			if (data->map_lines[i][len - 1] != '1' && 
				data->map_lines[i][len - 1] != ' ')
			{
				ft_dprintf(2, "Error\nMap not closed (right)\n");
				return (0);
			}
		}
		i++;
	}
	if (!check_internal_walls(data))
	{
		ft_dprintf(2, "Error\nMap has holes\n");
		return (0);
	}
	return (1);
}

static int	check_internal_walls(t_parse_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_line_count)
	{
		j = 0;
		while (data->map_lines[i][j])
		{
			if (data->map_lines[i][j] == '0' || 
				data->map_lines[i][j] == 'N' ||
				data->map_lines[i][j] == 'S' ||
				data->map_lines[i][j] == 'E' ||
				data->map_lines[i][j] == 'W')
			{
				if (is_exposed_to_void(data, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_exposed_to_void(t_parse_data *data, int y, int x)
{
	if (y == 0)
		return (1);
	if (x >= (int)ft_strlen(data->map_lines[y - 1]))
		return (1);
	if (data->map_lines[y - 1][x] == ' ')
		return (1);
	if (y == data->map_line_count - 1)
		return (1);
	if (x >= (int)ft_strlen(data->map_lines[y + 1]))
		return (1);
	if (data->map_lines[y + 1][x] == ' ')
		return (1);
	if (x == 0)
		return (1);
	if (data->map_lines[y][x - 1] == ' ')
		return (1);
	if (x >= (int)ft_strlen(data->map_lines[y]) - 1)
		return (1);
	if (data->map_lines[y][x + 1] == ' ')
		return (1);
	return (0);
}