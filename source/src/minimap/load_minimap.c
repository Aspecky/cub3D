/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:22:42 by mtarrih           #+#    #+#             */
/*   Updated: 2026/01/11 19:47:26 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "loaders.h"
#include "minimap.h"
#include <unistd.h>
#include "ftlibc/ft_stdio.h"

bool	load_minimap(void)
{
	if (!init_minimap())
	{
		dputstr("Failed to load minimap", STDERR_FILENO);
		return (false);
	}
	bind_loop(g_hookservice, minimap_bind, NULL, 0);
	return (true);
}
