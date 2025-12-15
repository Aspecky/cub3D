/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:20:31 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/01 19:12:35 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

int parse_file(char *filename)
{
    t_parse_data data;
    int fd;

    if (!validate_extension(filename))
    {
        ft_dprintf(2, "Error\nInvalid file extension (must be .cub)\n");
        return (0);
    }
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_dprintf(2, "Error\nCannot open file: %s\n", filename);
        return (0);
    }
    init_parse_data(&data);
    if (!parse_content(fd, &data))
    {
        close(fd);
        free_parse_data(&data);
        return (0);
    }
    close(fd);
    if (!validate_data(&data))
    {
        free_parse_data(&data);
        return (0);
    }
    if (!load_into_globals(&data))
    {
        free_parse_data(&data);
        return (0);
    }
    free_parse_data(&data);
    return (1);
}

int validate_extension(char *filename)
{
    int len;
    
    if (!filename)
        return (0);
    
    len = ft_strlen(filename);
    if (len < 5)
        return (0);
    if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
        return (0);
    
    return (1);
}
