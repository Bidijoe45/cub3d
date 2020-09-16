/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 11:14:34 by apavel            #+#    #+#             */
/*   Updated: 2020/09/01 10:24:32 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

#include <math.h>
#include <stdlib.h>
#include "image.h"
#include "../vector/vector.h"

typedef struct s_line {
	int dx;
	int dy;
	int steps;
	float x_inc;
	float y_inc;
} t_line;

void	pixel_put(t_img *vars, int x, int y, int color);
void	draw_line(t_img *img, t_point start, t_point end, unsigned long color);

#endif