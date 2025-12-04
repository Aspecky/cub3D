/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:05:33 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/04 17:10:34 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#include <stdint.h>

enum e_cell: uint8_t {
	CELL_EMPTY,
	CELL_WALL,
	CELL_DOOR,
};

#endif
