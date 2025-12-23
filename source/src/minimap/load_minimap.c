/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:22:42 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/23 19:23:31 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "loaders.h"
#include "minimap.h"

bool	load_minimap(void)
{
	if (!init_minimap())
		return (false);
	bind_loop(g_hookservice, minimap_bind, NULL, 0);
	return (true);
}
