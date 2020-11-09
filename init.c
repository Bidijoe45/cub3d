/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:42:39 by apavel            #+#    #+#             */
/*   Updated: 2020/11/06 11:59:10 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_dir(t_vars *vars)
{
	vars->player.dir_x = 0;
	vars->player.dir_y = 0;
	vars->player.plane_x = 0;
	vars->player.plane_y = 0;
}

void	init_map(t_parser *parsed_data, t_vars *vars)
{
	vars->map.height = parsed_data->map_height;
	vars->map.width = parsed_data->map_width;
	vars->map.map = parsed_data->map;
}

void	init_player(t_parser *parsed_data, t_vars *vars)
{
	vars->player.pos_x = parsed_data->player_y + 0.5;
	vars->player.pos_y = parsed_data->player_x + 0.5;
	set_player_dir(vars, parsed_data->player_dir);
	vars->player.speed = 0.07;
	vars->player.rot_speed = 0.05;
}

void	init_render_data(t_vars *vars)
{
	vars->render.map_x = 0;
	vars->render.map_y = 0;
	vars->render.step_x = 0;
	vars->render.step_y = 0;
	vars->render.hit = 0;
	vars->render.side = 0;
	vars->render.draw_start = 0;
	vars->render.draw_end = 0;
	vars->render.camera_x = 0;
	vars->render.ray_dir_x = 0;
	vars->render.ray_dir_y = 0;
	vars->render.side_dist_x = 0;
	vars->render.side_dist_y = 0;
	vars->render.delta_dist_x = 0;
	vars->render.delta_dist_y = 0;
	vars->render.prep_wall_dist = 0;
	vars->render.line_height = 0;
	vars->render.i = 0;
	vars->render.wall_x = 0;
	vars->render.color = 0;
	vars->render.tex_x = 0;
	vars->render.step = 0;
	vars->render.x = 0;
}

int		init_vars(t_parser *parsed_data, t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->window.height = parsed_data->w_height;
	vars->window.width = parsed_data->w_width;
	check_window_resolution(vars);
	init_map(parsed_data, vars);
	init_player(parsed_data, vars);
	vars->sprite_number = 0;
	vars->sprite_number = parsed_data->sprite_number;
	vars->sprite_order = parsed_data->sprite_order;
	vars->cealing_color = create_rgb(parsed_data->c_c[0],
		parsed_data->c_c[1], parsed_data->c_c[2]);
	vars->floor_color = create_rgb(parsed_data->f_c[0],
		parsed_data->f_c[1], parsed_data->f_c[2]);
	set_textures_paths(parsed_data, vars);
	if (check_textures_files(vars) == 0)
		return (0);
	load_textures(vars);
	if (valid_textures(vars) == 0)
		return (0);
	vars->p_window = mlx_new_window(vars->mlx, vars->window.width,
		vars->window.height, "cub3d");
	vars->zbuffer = malloc(sizeof(float) * vars->window.width);
	init_render_data(vars);
	return (1);
}
