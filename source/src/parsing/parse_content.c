/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:15:00 by kaneddam          #+#    #+#             */
/*   Updated: 2026/01/06 16:46:01 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	parse_config_lines(int fd, t_lninfo *lninfo, t_parsing *data)
{
	ssize_t	ret;
	int		config_count;

	config_count = 0;
	while (config_count < 6)
	{
		ret = dgetline(fd, lninfo);
		if (ret == -1 || ret == 0)
		{
			dputstr("Error\n", 2);
			return (0);
		}
		if (is_empty_line(lninfo->line))
			continue ;
		if (parse_line(lninfo->line, data))
			config_count++;
		else
			return (0);
	}
	return (1);
}

int	parse_content(int fd, t_parsing *data)
{
	t_lninfo	lninfo;

	ft_memset(&lninfo, 0, sizeof(t_lninfo));
	if (!parse_config_lines(fd, &lninfo, data))
	{
		free(lninfo.line);
		free(lninfo.store);
		return (0);
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
