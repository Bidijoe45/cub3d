/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 11:14:34 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 12:11:06 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "../cub3d.h"
# include <math.h>
# include <stdlib.h>
# include "image.h"

typedef struct	s_line {
	int			dx;
	int			dy;
	int			steps;
	float		x_inc;
	float		y_inc;
}				t_line;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

void			pixel_put(t_img *vars, int x, int y, int color);
void			draw_line(t_img *img, t_point start, t_point end,
							unsigned long color);
void			draw_ceailing(t_vars *vars, t_img *img);
void			draw_wall(t_vars *vars, t_img *img);
void			draw_floor(t_vars *vars, t_img *img);
void			draw_sprite(t_vars *vars, t_img *img,
					t_render_sprite *sprite, int stripe);
#endif
