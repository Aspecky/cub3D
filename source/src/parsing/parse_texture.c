/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by kamar             #+#    #+#             */
/*   Updated: 2026/01/06 16:31:18 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_texture(char *path_str, char **dest)
{
	char	*start;
	char	*end;
	int		len;

	start = path_str;
	while (*start == ' ' || *start == '\t')
		start++;
	end = start;
	while (*end && *end != '\n' && *end != '\r' && *end != ' ' && *end != '\t')
		end++;
	len = end - start;
	if (len == 0)
	{
		dputstr("Error, empty texture path\n", 2);
		return (0);
	}
	*dest = malloc(len + 1);
	if (!dest)
		return (0);
	ft_memcpy(*dest, start, len);
	(*dest)[len] = '\0';
	return (1);
}

int	is_wall(char c)
{
	return (c == '1');
}

int	is_void(char c)
{
	return (c == ' ');
}

int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'D');
}
