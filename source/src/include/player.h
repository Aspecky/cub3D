/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 16:19:20 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/24 21:08:08 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "consts.h"
# include <stdbool.h>

typedef struct s_jump_state
{
	bool	animating;
	bool	jumping;
	bool	falling;
	double	dt;
	double	hold_time;
	double	jump_boost;
}			t_jump_state;

bool	init_view_model(void);

void	cursor_hook(double xpos, double ypos, void *param);
void	rotate_bind(void *param);
void	walk_bind(void *param);
void	jump_bind(void *param);
void	bobbing_bind(void *param);

#endif
