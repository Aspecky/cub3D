/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamar <kamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by kamar             #+#    #+#             */
/*   Updated: 2025/12/29 12:54:43 by kamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		if (!*start || (*start != '-' && (*start < '0' || *start > '9')))
		{
			dputstr("Error: invalid color format\n", 2);
			return (0);
		}
		values[i] = ft_atoi(start);
		if (values[i] < 0 || values[i] > 255)
		{
			dputstr("Error: color value must be between 0 and 255\n", 2);
			return (0);
		}
		while (*start && *start != ',' && *start != ' '
			&& *start != '\t' && *start != '\n')
			start++;
		if (i < 2)
		{
			if (*start != ',')
			{
				dputstr("Error: color values must be separated by commas\n", 2);
				return (0);
			}
			start++;
		}
		i++;
	}
	color->r = (uint8_t)values[0];
	color->g = (uint8_t)values[1];
	color->b = (uint8_t)values[2];
	color->alpha = 255;
	return (1);
}
