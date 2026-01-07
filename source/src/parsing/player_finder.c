/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:00:00 by kaneddam          #+#    #+#             */
/*   Updated: 2026/01/06 16:43:58 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_and_save_player(t_parsing *data, int i, int j, int *count)
{
	if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
		|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
	{
		data->player_dir = data->map[i][j];
		data->player_pos.x = j;
		data->player_pos.y = i;
		(*count)++;
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
			count_and_save_player(data, i, j, &player_count);
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
