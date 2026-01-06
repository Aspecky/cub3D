/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamar <kamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 00:00:00 by kamar             #+#    #+#             */
/*   Updated: 2026/01/05 16:49:29 by kamar            ###   ########.fr       */
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

int	parse_map(int fd, t_lninfo *lninfo, t_parsing *data)
{
	ssize_t	ret;
	int		len;
	int		capacity;

	ret = dgetline(fd, lninfo);
	while (ret > 0 && is_empty_line(lninfo->line))
		ret = dgetline(fd, lninfo);
	if (ret <= 0)
	{
		dputstr("Error: no map found\n", 2);
		return (0);
	}
	data->map_height = 0;
	capacity = 100;
	data->map = malloc(sizeof(char *) * capacity);
	if (!data->map)
		return (0);
	while (ret > 0)
	{
		if (is_empty_line(lninfo->line))
		{
			dputstr("Error: empty line in map\n", 2);
			return (0);
		}
		if (!validate_map_line(lninfo->line))
			return (0);
		if (data->map_height >= capacity)
		{
			capacity *= 2;
			data->map = ft_realloc(data->map, sizeof(char *) * (capacity / 2),
					sizeof(char *) * capacity);
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
		ret = dgetline(fd, lninfo);
	}
	if (data->map_height == 0)
	{
		dputstr("Error: empty map\n", 2);
		return (0);
	}
	if (!find_player(data))
		return (0);
	if (!check_map_borders(data))
		return (0);
	if (!validate_doors(data))
		return (0);
	return (1);
}

int	parse_content(int fd, t_parsing *data)
{
	t_lninfo	lninfo;
	ssize_t		ret;
	int			config_count;

	ft_memset(&lninfo, 0, sizeof(t_lninfo));
	lninfo.store = NULL;
	lninfo._store_size = 0;
	lninfo.line = NULL;
	lninfo.line_size = 0;
	config_count = 0;
	while (config_count < 6)
	{
		ret = dgetline(fd, &lninfo);
		if (ret == -1 || ret == 0)
		{
			dputstr("Error\n", 2);
			free(lninfo.line);
			free(lninfo.store);
			return (0);
		}
		if (is_empty_line(lninfo.line))
			continue ;
		if (parse_line(lninfo.line, data))
			config_count++;
		else
		{
			free(lninfo.line);
			free(lninfo.store);
			return (0);
		}
	}
	if (!parse_map(fd, &lninfo, data))
	{
		free(lninfo.line);
		free(lninfo.store);
		return (0);
	}
	free(lninfo.line);
	free(lninfo.store);
	return (1);
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
