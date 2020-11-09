/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:32:38 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 12:10:25 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_ray_dir(t_vars *vars)
{
	vars->render.ray_dir_x = vars->player.dir_x
		+ vars->player.plane_x * vars->render.camera_x;
	vars->render.ray_dir_y = vars->player.dir_y
		+ vars->player.plane_y * vars->render.camera_x;
}

void	calc_delta_dist(t_vars *vars)
{
	if (vars->render.ray_dir_y == 0)
		vars->render.delta_dist_x = 0;
	else
		vars->render.delta_dist_x = ((vars->render.ray_dir_x == 0)
			? 1 : fabs(1 / vars->render.ray_dir_x));
	if (vars->render.ray_dir_x == 0)
		vars->render.delta_dist_y = 0;
	else
		vars->render.delta_dist_y = ((vars->render.ray_dir_y == 0)
			? 1 : fabs(1 / vars->render.ray_dir_y));
}

void	calc_side_dist(t_vars *vars)
{
	if (vars->render.ray_dir_x < 0)
	{
		vars->render.step_x = -1;
		vars->render.side_dist_x = (vars->player.pos_x - vars->render.map_x)
			* vars->render.delta_dist_x;
	}
	else
	{
		vars->render.step_x = 1;
		vars->render.side_dist_x = (vars->render.map_x + 1.0
		- vars->player.pos_x) * vars->render.delta_dist_x;
	}
	if (vars->render.ray_dir_y < 0)
	{
		vars->render.step_y = -1;
		vars->render.side_dist_y = (vars->player.pos_y
			- vars->render.map_y) * vars->render.delta_dist_y;
	}
	else
	{
		vars->render.step_y = 1;
		vars->render.side_dist_y = (vars->render.map_y + 1.0
			- vars->player.pos_y) * vars->render.delta_dist_y;
	}
}

void	calc_wall_texture(t_vars *vars)
{
	vars->render.line_height = (vars->window.height
		/ vars->render.prep_wall_dist);
	vars->render.draw_start = -vars->render.line_height / 2
		+ vars->window.height / 2;
	if (vars->render.draw_start < 0)
		vars->render.draw_start = 0;
	vars->render.draw_end = vars->render.line_height / 2
		+ vars->window.height / 2;
	if (vars->render.draw_end >= vars->window.height)
		vars->render.draw_end = vars->window.height - 1;
	if (vars->render.side == 0)
		vars->render.wall_x = vars->player.pos_y + vars->render.prep_wall_dist
		* vars->render.ray_dir_y;
	else
		vars->render.wall_x = vars->player.pos_x + vars->render.prep_wall_dist
		* vars->render.ray_dir_x;
	vars->render.wall_x -= floor(vars->render.wall_x);
	vars->render.tex_x = (int)(vars->render.wall_x * (float)64);
	if (vars->render.side == 0 && vars->render.ray_dir_x > 0)
		vars->render.tex_x = 64 - vars->render.tex_x - 1;
	if (vars->render.side == 1 && vars->render.ray_dir_y < 0)
		vars->render.tex_x = 64 - vars->render.tex_x - 1;
	vars->render.step = 1 * 64 / vars->render.line_height;
	vars->render.tex_pos = (vars->render.draw_start - vars->window.height / 2
	+ vars->render.line_height / 2) * vars->render.step;
}

void	calc_dist_to_sprites(t_vars *vars)
{
	int i;

	i = 0;
	while (i < vars->sprite_number)
	{
		vars->sprite_order[i].distance =
		((vars->player.pos_x - vars->sprite_order[i].x)
		* (vars->player.pos_x - vars->sprite_order[i].x)
		+ (vars->player.pos_y - vars->sprite_order[i].y)
		* (vars->player.pos_y - vars->sprite_order[i].y));
		i++;
	}
}
