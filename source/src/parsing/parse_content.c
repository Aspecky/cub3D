/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:33:47 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/01 20:43:19 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <string.h>
#include <stdlib.h>
#include "ftlibc/ft_string.h"

int parse_content(int fd, t_parse_data *data)
{
    t_lninfo lninfo;
    ssize_t ret;
    int config_count;
    
    ft_memset(&lninfo, 0, sizeof(t_lninfo));
    lninfo.store = NULL;
    lninfo._store_size = 0;
    lninfo.line = NULL;
    lninfo.line_size = 0;
    
    config_count = 0;
    
    while (config_count < 6)
    {
        ret = dgetline(fd, &lninfo);
        
        if (ret == -1)
        {
            ft_dprintf(2, "Error\nRead error\n");
            free(lninfo.line);
            free(lninfo.store);
            return (0);
        }
        
        if (ret == 0)
        {
            ft_dprintf(2, "Error\nMissing configuration elements\n");
            free(lninfo.line);
            free(lninfo.store);
            return (0);
        }
    
        if (is_empty_line(lninfo.line))
            continue;
     
        if (parse_config_line(lninfo.line, data))
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

int is_empty_line(char *line)
{
    int i;
    
    if (!line)
        return (1);
    
    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && 
            line[i] != '\n' && line[i] != '\r')
            return (0);
        i++;
    }
    return (1);
}