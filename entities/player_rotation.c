/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:53:50 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 12:09:18 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_vars *vars)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = vars->player.dir_x;
	vars->player.dir_x = vars->player.dir_x * cos(vars->player.rot_speed)
						- vars->player.dir_y * sin(vars->player.rot_speed);
	vars->player.dir_y = old_dir_x * sin(vars->player.rot_speed)
						+ vars->player.dir_y * cos(vars->player.rot_speed);
	old_plane_x = vars->player.plane_x;
	vars->player.plane_x = vars->player.plane_x * cos(vars->player.rot_speed)
						- vars->player.plane_y * sin(vars->player.rot_speed);
	vars->player.plane_y = old_plane_x * sin(vars->player.rot_speed)
						+ vars->player.plane_y * cos(vars->player.rot_speed);
}

void	rotate_right(t_vars *vars)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = vars->player.dir_x;
	vars->player.dir_x = vars->player.dir_x * cos(-(vars->player.rot_speed))
						- vars->player.dir_y * sin(-(vars->player.rot_speed));
	vars->player.dir_y = old_dir_x * sin(-(vars->player.rot_speed))
						+ vars->player.dir_y * cos(-(vars->player.rot_speed));
	old_plane_x = vars->player.plane_x;
	vars->player.plane_x = vars->player.plane_x * cos(-(vars->player.rot_speed))
						- vars->player.plane_y * sin(-(vars->player.rot_speed));
	vars->player.plane_y = old_plane_x * sin(-(vars->player.rot_speed))
						+ vars->player.plane_y * cos(-(vars->player.rot_speed));
}
