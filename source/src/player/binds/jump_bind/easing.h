/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarrih <mtarrih@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 20:51:37 by mtarrih           #+#    #+#             */
/*   Updated: 2025/12/24 21:07:28 by mtarrih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASING_H
# define EASING_H

double	lerp(double a, double b, double t);
double	ease_out(double t);
double	ease_in(double t);

#endif
