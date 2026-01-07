/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by kamar             #+#    #+#             */
/*   Updated: 2026/01/06 16:38:02 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_color_value(char **start, int *value)
{
	if (!**start || (**start != '-' && (**start < '0' || **start > '9')))
	{
		dputstr("Error: invalid color format\n", 2);
		return (0);
	}
	*value = ft_atoi(*start);
	if (*value < 0 || *value > 255)
	{
		dputstr("Error: color value must be between 0 and 255\n", 2);
		return (0);
	}
	while (**start && **start != ',' && **start != ' ' && **start != '\t'
		&& **start != '\n')
		(*start)++;
	return (1);
}

static int	skip_to_next_value(char **start, int i)
{
	if (i < 2)
	{
		if (**start != ',')
		{
			dputstr("Error: color values must be separated by commas\n", 2);
			return (0);
		}
		(*start)++;
	}
	return (1);
}

int	parse_color(char *color_str, t_color_rgb *color)
{
	char	*start;
	int		values[3];
	int		i;

	start = color_str;
	while (*start == ' ' || *start == '\t')
		start++;
	i = 0;
	while (i < 3)
	{
		if (!parse_color_value(&start, &values[i]))
			return (0);
		if (!skip_to_next_value(&start, i))
			return (0);
		i++;
	}
	color->r = (uint8_t)values[0];
	color->g = (uint8_t)values[1];
	color->b = (uint8_t)values[2];
	color->alpha = 255;
	return (1);
}
