/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamar <kamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by kamar             #+#    #+#             */
/*   Updated: 2025/12/29 12:54:36 by kamar            ###   ########.fr       */
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
