/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:39:28 by apavel            #+#    #+#             */
/*   Updated: 2020/11/04 13:42:40 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "../entities/sprite.h"

int		count_sprites(t_parser *vars)
{
	int		x;
	int		y;
	int		sprite_number;

	sprite_number = 0;
	y = 0;
	while (y < vars->map_height)
	{
		x = 0;
		while (x < vars->map_width)
		{
			if (vars->map[y][x] == '8')
				sprite_number++;
			x++;
		}
		y++;
	}
	return (sprite_number);
}

void	detect_sprites(t_parser *vars)
{
	int		x;
	int		y;
	int		i;

	vars->sprite_number = count_sprites(vars);
	vars->sprite_order = malloc(vars->sprite_number * sizeof(t_sprite));
	y = 0;
	i = 0;
	while (y < vars->map_height)
	{
		x = 0;
		while (x < vars->map_width)
		{
			if (vars->map[y][x] == '8')
			{
				vars->sprite_order[i].y = (float)x + 0.5;
				vars->sprite_order[i].x = (float)y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
}
