/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:15:00 by kaneddam          #+#    #+#             */
/*   Updated: 2026/01/06 19:02:49 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	store_map_line(t_lninfo *lninfo, t_parsing *data, int *capacity)
{
	int	len;

	if (data->map_height >= *capacity)
	{
		*capacity *= 2;
		data->map = ft_realloc(data->map, sizeof(char *) * (*capacity / 2),
				sizeof(char *) * *capacity);
		if (!data->map)
			return (0);
	}
	len = ft_strlen(lninfo->line);
	if (len > 0 && lninfo->line[len - 1] == '\n')
		len--;
	data->map[data->map_height] = malloc(len + 1);
	if (!data->map[data->map_height])
		return (0);
	ft_memcpy(data->map[data->map_height], lninfo->line, len);
	data->map[data->map_height][len] = '\0';
	if (len > data->map_width)
		data->map_width = len;
	data->map_height++;
	return (1);
}

static int	read_map_lines(int fd, t_lninfo *lninfo, t_parsing *data)
{
	ssize_t	ret;
	int		capacity;

	capacity = 100;
	data->map = malloc(sizeof(char *) * capacity);
	if (!data->map)
		return (0);
	ret = dgetline(fd, lninfo);
	while (ret > 0)
	{
		if (is_empty_line(lninfo->line))
			break ;
		if (!validate_map_line(lninfo->line))
			return (0);
		if (!store_map_line(lninfo, data, &capacity))
			return (0);
		ret = dgetline(fd, lninfo);
	}
	return (1);
}

int	parse_map(int fd, t_lninfo *lninfo, t_parsing *data)
{
	ssize_t	ret;

	ret = dgetline(fd, lninfo);
	while (ret > 0 && is_empty_line(lninfo->line))
		ret = dgetline(fd, lninfo);
	if (ret <= 0)
	{
		dputstr("Error: no map found\n", 2);
		return (0);
	}
	data->map_height = 0;
	if (!read_map_lines(fd, lninfo, data))
		return (0);
	if (!find_player(data))
		return (0);
	if (!check_map_borders(data))
		return (0);
	if (!validate_doors(data))
		return (0);
	return (1);
}
