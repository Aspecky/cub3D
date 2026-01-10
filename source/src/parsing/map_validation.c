/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:11:22 by kaneddam          #+#    #+#             */
/*   Updated: 2026/01/10 21:25:50 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

static int	check_row_space_leaks(t_parsing *data, int i)
{
	int	j;

	j = 0;
	while (j < (int)ft_strlen(data->map[i]))
	{
		if (!check_space_leaks(data, i, j))
			return (0);
		j++;
	}
	return (1);
}

static int	check_row_borders(t_parsing *data, int i, int first, int last)
{
	if (i == 0 || i == data->map_height - 1)
	{
		if (!check_top_bottom_borders(data, i, first, last))
			return (0);
	}
	else if (!check_side_borders(data, i, first, last))
		return (0);
	return (1);
}

int	find_first_non_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	check_map_borders(t_parsing *data)
{
	int	i;
	int	first_char;
	int	last_char;

	i = 0;
	while (i < data->map_height)
	{
		first_char = find_first_non_space(data->map[i]);
		last_char = find_last_non_space(data->map[i]);
		if (!check_row_borders(data, i, first_char, last_char))
			return (0);
		if (!check_row_space_leaks(data, i))
			return (0);
		i++;
	}
	return (1);
}
