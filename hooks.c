/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:38:47 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 12:42:13 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->p_window);
	exit(0);
}

int		key_release_handler(int keycode, t_vars *vars)
{
	if (keycode == 123)
		vars->keys.larrow_key = 0;
	if (keycode == 124)
		vars->keys.rarrow_key = 0;
	if (keycode == 13)
		vars->keys.w_key = 0;
	if (keycode == 1)
		vars->keys.s_key = 0;
	if (keycode == 0)
		vars->keys.a_key = 0;
	if (keycode == 2)
		vars->keys.d_key = 0;
	return (1);
}

int		key_press_handler(int keycode, t_vars *vars)
{
	if (keycode == 53)
		close_window(vars);
	if (keycode == 123)
		vars->keys.larrow_key = 1;
	if (keycode == 124)
		vars->keys.rarrow_key = 1;
	if (keycode == 13)
		vars->keys.w_key = 1;
	if (keycode == 1)
		vars->keys.s_key = 1;
	if (keycode == 0)
		vars->keys.a_key = 1;
	if (keycode == 2)
		vars->keys.d_key = 1;
	return (1);
}

void	create_hooks(t_vars *vars)
{
	mlx_hook(vars->p_window, 2, 0L, key_press_handler, vars);
	mlx_hook(vars->p_window, 3, 0L, key_release_handler, vars);
	mlx_hook(vars->p_window, 17, 0L, close_window, vars);
	mlx_loop_hook(vars->mlx, render, vars);
	mlx_loop(vars->mlx);
}
