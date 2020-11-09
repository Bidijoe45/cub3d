/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 11:15:13 by apavel            #+#    #+#             */
/*   Updated: 2020/11/06 12:58:15 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_ceailing(t_vars *vars, t_img *img)
{
	int i;

	i = 0;
	while (i < vars->render.draw_start)
	{
		pixel_put(img, vars->render.x, i, vars->cealing_color);
		i++;
	}
}

void	draw_wall(t_vars *vars, t_img *img)
{
	int y;
	int tex_y;

	y = vars->render.draw_start;
	while (y < vars->render.draw_end)
	{
		tex_y = (int)vars->render.tex_pos;
		vars->render.tex_pos += vars->render.step;
		if (vars->render.step_x == -1 && vars->render.side == 0)
			vars->render.color = ((int *)vars->texture_north.addr)
					[vars->texture_north.width * tex_y + vars->render.tex_x];
		if (vars->render.step_x == 1 && vars->render.side == 0)
			vars->render.color = ((int *)vars->texture_south.addr)
					[vars->texture_south.width * tex_y + vars->render.tex_x];
		if (vars->render.step_y == -1 && vars->render.side == 1)
			vars->render.color = ((int *)vars->texture_west.addr)
					[vars->texture_west.width * tex_y + vars->render.tex_x];
		if (vars->render.step_y == 1 && vars->render.side == 1)
			vars->render.color = ((int *)vars->texture_east.addr)
					[vars->texture_east.width * tex_y + vars->render.tex_x];
		pixel_put(img, vars->render.x, y, vars->render.color);
		y++;
	}
}

void	draw_floor(t_vars *vars, t_img *img)
{
	int i;

	i = vars->render.draw_end;
	while (i < vars->window.height)
	{
		pixel_put(img, vars->render.x, i, vars->floor_color);
		i++;
	}
}

void	draw_sprite(t_vars *vars, t_img *img,
	t_render_sprite *sprite, int stripe)
{
	int	d;
	int	y;

	sprite->tex_x = (int)(256 * (stripe - (-sprite->width / 2
	+ sprite->sprite_screen_x)) * vars->sprite.width / sprite->width) / 256;
	if (sprite->transform_y > 0 && stripe > 0 && stripe < vars->window.width
		&& sprite->transform_y < vars->zbuffer[stripe])
	{
		y = sprite->draw_start_y;
		while (y < sprite->draw_end_y)
		{
			d = (y) * 256 - vars->window.height * 128 + sprite->height * 128;
			sprite->tex_y = ((d * vars->sprite.height) / sprite->height) / 256;
			sprite->color = ((int *)vars->sprite.addr)[vars->sprite.width
				* sprite->tex_y + sprite->tex_x];
			if (sprite->color != 0x000000)
				pixel_put(img, stripe, y, sprite->color);
			y++;
		}
	}
}
