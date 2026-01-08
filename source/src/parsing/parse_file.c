/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by kamar             #+#    #+#             */
/*   Updated: 2026/01/06 16:46:28 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_line(char *line, t_parsing *data)
{
	char	*trimmed;

	if (!line)
		return (0);
	trimmed = line;
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (parse_texture(trimmed + 3, &data->no_path));
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (parse_texture(trimmed + 3, &data->so_path));
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (parse_texture(trimmed + 3, &data->we_path));
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (parse_texture(trimmed + 3, &data->ea_path));
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		return (parse_color(trimmed + 2, &data->floor));
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		return (parse_color(trimmed + 2, &data->ceiling));
	dputstr("Error\n invalid config line", 2);
	return (0);
}

t_parsing	parse_file(char *file)
{
	t_parsing	data;
	int			fd;

	data.ok = false;
	if (!valid_cub(file))
	{
		dputstr("Error, invalid file extension\n, must be .cub\n", 2);
		return (data);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error, cannot open file %s\n", file);
		return (data);
	}
	init_parse(&data);
	if (!parse_content(fd, &data))
	{
		close(fd);
		free_parse(&data);
		return (data);
	}
	close(fd);
	data.ok = true;
	return (data);
}
