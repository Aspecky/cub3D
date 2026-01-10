/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:00:00 by kaneddam          #+#    #+#             */
/*   Updated: 2026/01/10 21:25:47 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_last_non_space(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && line[i] == ' ')
		i--;
	return (i);
}

int	check_top_bottom_borders(t_parsing *data, int i, int first, int last)
{
	int	j;

	j = first;
	while (j <= last)
	{
		if (data->map[i][j] != '1' && data->map[i][j] != ' ')
		{
			dputstr("Error: map must be surrounded by walls\n", 2);
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_side_borders(t_parsing *data, int i, int first, int last)
{
	if (first >= 0 && data->map[i][first] != '1')
	{
		dputstr("Error: map must be surrounded by walls\n", 2);
		return (0);
	}
	if (last >= 0 && data->map[i][last] != '1')
	{
		dputstr("Error: map must be surrounded by walls\n", 2);
		return (0);
	}
	return (1);
}

static int	is_outside_map(t_parsing *data, int x, int y)
{
	if (y < 0 || y >= data->map_height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(data->map[y]))
		return (1);
	return (0);
}

int	check_space_leaks(t_parsing *data, int i, int j)
{
	if (data->map[i][j] != '1' && data->map[i][j] != ' ')
	{
		if (is_outside_map(data, j, i - 1) || is_outside_map(data, j, i + 1)
			|| is_outside_map(data, j - 1, i) || is_outside_map(data, j + 1, i))
		{
			dputstr("Error: map must be surrounded by walls\n", 2);
			return (0);
		}
	}
	return (1);
}
