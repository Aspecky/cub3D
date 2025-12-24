/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:51:37 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/24 21:07:46 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "easing.h"

double	lerp(double a, double b, double t)
{
	return (a + (b - a) * t);
}

double	ease_out(double t)
{
	return (sin((t * M_PI) / 2));
}

double	ease_in(double t)
{
	return (1 - cos((t * M_PI) / 2));
}
