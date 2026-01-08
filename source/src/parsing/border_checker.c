/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   border_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:00:00 by kaneddam          #+#    #+#             */
/*   Updated: 2026/01/06 16:43:58 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_first_non_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

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

int	check_space_leaks(t_parsing *data, int i, int j)
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
	return (1);
}
