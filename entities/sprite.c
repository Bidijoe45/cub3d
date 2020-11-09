/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:40:10 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 12:09:24 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../render/draw.h"

void	swap(t_sprite *xp, t_sprite *yp)
{
	t_sprite temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void	sort_sprites(t_vars *vars, int n)
{
	int i;
	int j;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (vars->sprite_order[j].distance
				<= vars->sprite_order[j + 1].distance)
				swap(&vars->sprite_order[j], &vars->sprite_order[j + 1]);
			j++;
		}
		i++;
	}
}

void	init_sprite_vars(t_vars *vars,
	t_render_sprite *sprite, int sprite_number)
{
	sprite->x = vars->sprite_order[sprite_number].x - vars->player.pos_x;
	sprite->y = vars->sprite_order[sprite_number].y - vars->player.pos_y;
	sprite->inv_det = 1.0 / (vars->player.plane_x * vars->player.dir_y
	- vars->player.dir_x * vars->player.plane_y);
	sprite->transform_x = sprite->inv_det * (vars->player.dir_y * sprite->x
	- vars->player.dir_x * sprite->y);
	sprite->transform_y = sprite->inv_det * (-vars->player.plane_y * sprite->x
	+ vars->player.plane_x * sprite->y);
	sprite->sprite_screen_x = (int)((vars->window.width / 2)
	* (1 + sprite->transform_x / sprite->transform_y));
	sprite->height = abs((int)(vars->window.height / (sprite->transform_y)));
	sprite->draw_start_y = -sprite->height / 2 + vars->window.height / 2;
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->height / 2 + vars->window.height / 2;
	if (sprite->draw_end_y >= vars->window.height)
		sprite->draw_end_y = vars->window.height - 1;
	sprite->width = abs((int)(vars->window.height / (sprite->transform_y)));
	sprite->draw_start_x = -sprite->width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->width / 2 + sprite->sprite_screen_x;
	if (sprite->draw_end_x >= vars->window.width)
		sprite->draw_end_x = vars->window.width - 1;
}

void	display_sprites(t_vars *vars, t_img *img)
{
	t_render_sprite	sprite;
	int				i;
	int				stripe;

	i = 0;
	while (i < vars->sprite_number)
	{
		init_sprite_vars(vars, &sprite, i);
		stripe = sprite.draw_start_x;
		while (stripe < sprite.draw_end_x)
		{
			draw_sprite(vars, img, &sprite, stripe);
			stripe++;
		}
		i++;
	}
}
