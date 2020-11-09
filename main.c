/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:43:11 by apavel            #+#    #+#             */
/*   Updated: 2020/11/09 10:08:23 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned long	create_rgb(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

void			check_window_resolution(t_vars *vars)
{
	if (vars->window.width > 2432)
		vars->window.width = 2432;
	if (vars->window.height > 1368)
		vars->window.height = 1368;
}

void			set_player_dir(t_vars *vars, int player_dir)
{
	init_player_dir(vars);
	if (player_dir == 0)
	{
		vars->player.dir_y = 1;
		vars->player.plane_x = 0.66;
	}
	else if (player_dir == 90)
	{
		vars->player.dir_x = -1;
		vars->player.plane_y = 0.66;
	}
	else if (player_dir == 180)
	{
		vars->player.dir_y = -1;
		vars->player.plane_x = -0.66;
	}
	else if (player_dir == 270)
	{
		vars->player.dir_x = 1;
		vars->player.plane_y = -0.66;
	}
}

int				check_args(t_vars *vars, int argc, char **argv)
{
	if (argc == 2)
		return (0);
	else if (argc == 3 && ft_strncmp(argv[2], "--save\0", 8) == 0)
	{
		vars->create_image = 1;
		return (1);
	}
	return (-1);
}

int				main(int argc, char **argv)
{
	t_vars		*vars;
	t_parser	*parsed_data;
	int			args;

	parsed_data = malloc(sizeof(t_parser));
	vars = malloc(sizeof(t_vars));
	args = check_args(vars, argc, argv);
	if (args == -1)
	{
		write(1, "Error\n", 7);
		return (0);
	}
	if (read_file(parsed_data, argv[1]) == 0
		|| init_vars(parsed_data, vars) == 0)
	{
		write(1, "Error\n", 7);
		return (0);
	}
	if (args == 1)
	{
		render(vars);
		return (0);
	}
	create_hooks(vars);
	return (0);
}
