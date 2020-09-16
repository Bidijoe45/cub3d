/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 11:15:13 by apavel            #+#    #+#             */
/*   Updated: 2020/09/01 11:59:24 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void            pixel_put(t_img *vars, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= 640 || y < 0 || y >= 480)
        return ;
    dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void    draw_line(t_img *img, t_point start, t_point end, unsigned long color)
{
    float   x;
    float   y;
    int     i;
    t_line  line;
    line.dx = end.x - start.x;
    line.dy = end.y - start.y;
    line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy);
    line.x_inc = line.dx / (float)line.steps;
    line.y_inc = line.dy / (float)line.steps;
    x = start.x;
    y = start.y;
    i = 0;
    while (i <= line.steps)
    {
        pixel_put(img, x, y, color);
        x += line.x_inc;
        y += line.y_inc;
        i++;
    }
}