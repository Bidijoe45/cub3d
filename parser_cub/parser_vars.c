/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:39:42 by apavel            #+#    #+#             */
/*   Updated: 2020/11/04 13:39:43 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int		check_variables(t_parser *vars)
{
	if (vars->w_height == -1 || vars->w_width == -1
		|| vars->texture_north == NULL || vars->texture_south == NULL
		|| vars->texture_east == NULL || vars->texture_west == NULL
		|| vars->sprite_texture == NULL || vars->f_c[0] == -1
		|| vars->f_c[1] == -1 || vars->f_c[2] == -1
		|| vars->c_c[0] == -1 || vars->c_c[1] == -1
		|| vars->c_c[2] == -1)
		return (0);
	return (1);
}

void	initialize_vars(t_parser *vars)
{
	vars->w_width = -1;
	vars->w_height = -1;
	vars->texture_north = NULL;
	vars->texture_south = NULL;
	vars->texture_east = NULL;
	vars->texture_west = NULL;
	vars->sprite_texture = NULL;
	vars->f_c[0] = -1;
	vars->f_c[1] = -1;
	vars->f_c[2] = -1;
	vars->c_c[0] = -1;
	vars->c_c[1] = -1;
	vars->c_c[2] = -1;
	vars->map_height = 0;
	vars->map_width = 0;
	vars->player_x = -1;
	vars->player_y = -1;
	vars->player_dir = -1;
}
