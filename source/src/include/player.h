/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:19:20 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/20 16:58:03 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
#define PLAYER_H

#include "consts.h"
#include <stdbool.h>

bool init_view_model(void);

void cursor_hook(double xpos, double ypos, void *param);
void rotate_bind(void *param);
void walk_bind(void *param);
void jump_bind(void *param);
void view_model_bobbing_bind(void *param);

#endif
