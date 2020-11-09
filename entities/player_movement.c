/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:52:13 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 12:09:07 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_vars *vars)
{
	int new_x;
	int new_y;

	new_x = (int)(vars->player.pos_x + vars->player.dir_x
			* vars->player.speed);
	if (vars->map.map[new_x][(int)vars->player.pos_y] == '0')
		vars->player.pos_x += vars->player.dir_x * vars->player.speed;
	new_y = (int)(vars->player.pos_y + vars->player.dir_y
			* vars->player.speed);
	if (vars->map.map[(int)vars->player.pos_x][new_y] == '0')
		vars->player.pos_y += vars->player.dir_y * vars->player.speed;
}

void	move_backward(t_vars *vars)
{
	int new_x;
	int new_y;

	new_x = (int)(vars->player.pos_x - vars->player.dir_x
			* vars->player.speed);
	if (vars->map.map[new_x][(int)vars->player.pos_y] == '0')
		vars->player.pos_x -= vars->player.dir_x * vars->player.speed;
	new_y = (int)(vars->player.pos_y - vars->player.dir_y
		* vars->player.speed);
	if (vars->map.map[(int)vars->player.pos_x][new_y] == '0')
		vars->player.pos_y -= vars->player.dir_y * vars->player.speed;
}

void	move_left(t_vars *vars)
{
	int new_x;
	int new_y;

	new_x = (int)(vars->player.pos_x + (vars->player.dir_y * -1)
			* vars->player.speed);
	if (vars->map.map[new_x][(int)vars->player.pos_y] == '0')
		vars->player.pos_x += (vars->player.dir_y * -1) * vars->player.speed;
	new_y = (int)(vars->player.pos_y + vars->player.dir_x
			* vars->player.speed);
	if (vars->map.map[(int)vars->player.pos_x][new_y] == '0')
		vars->player.pos_y += vars->player.dir_x * vars->player.speed;
}

void	move_right(t_vars *vars)
{
	int new_x;
	int new_y;

	new_x = (int)(vars->player.pos_x + vars->player.dir_y
			* vars->player.speed);
	if (vars->map.map[new_x][(int)vars->player.pos_y] == '0')
		vars->player.pos_x += (vars->player.dir_y) * vars->player.speed;
	new_y = (int)(vars->player.pos_y + (vars->player.dir_x * -1)
			* vars->player.speed);
	if (vars->map.map[(int)vars->player.pos_x][new_y] == '0')
		vars->player.pos_y += (vars->player.dir_x * -1) * vars->player.speed;
}

void	move_player(t_vars *vars)
{
	if (vars->keys.w_key == 1)
		move_forward(vars);
	if (vars->keys.s_key == 1)
		move_backward(vars);
	if (vars->keys.a_key == 1)
		move_left(vars);
	if (vars->keys.d_key == 1)
		move_right(vars);
	if (vars->keys.larrow_key == 1)
		rotate_left(vars);
	if (vars->keys.rarrow_key == 1)
		rotate_right(vars);
}
