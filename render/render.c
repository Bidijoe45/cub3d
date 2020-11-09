/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 12:44:10 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 12:11:38 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "draw.h"
#include "img_to_bmp.h"
#include "calc.h"

void	set_map_pos(t_vars *vars)
{
	vars->render.map_x = (int)vars->player.pos_x;
	vars->render.map_y = (int)vars->player.pos_y;
}

void	set_side(t_vars *vars)
{
	if (vars->render.side == 0)
		vars->render.prep_wall_dist = (vars->render.map_x
		- vars->player.pos_x + (1 - vars->render.step_x) / 2)
		/ vars->render.ray_dir_x;
	else
		vars->render.prep_wall_dist = (vars->render.map_y - vars->player.pos_y
		+ (1 - vars->render.step_y) / 2) / vars->render.ray_dir_y;
}

void	cast_ray(t_vars *vars)
{
	while (vars->render.hit == 0)
	{
		if (vars->render.side_dist_x < vars->render.side_dist_y)
		{
			vars->render.side_dist_x += vars->render.delta_dist_x;
			vars->render.map_x += vars->render.step_x;
			vars->render.side = 0;
		}
		else
		{
			vars->render.side_dist_y += vars->render.delta_dist_y;
			vars->render.map_y += vars->render.step_y;
			vars->render.side = 1;
		}
		if (vars->map.map[vars->render.map_x][vars->render.map_y] == '1')
			vars->render.hit = 1;
	}
}

void	shoot_ray(t_vars *vars, t_img *img)
{
	vars->render.step_x = 0;
	vars->render.step_y = 0;
	vars->render.hit = 0;
	vars->render.camera_x = 2 * vars->render.x
			/ (float)vars->window.width - 1;
	calc_ray_dir(vars);
	calc_delta_dist(vars);
	set_map_pos(vars);
	calc_side_dist(vars);
	cast_ray(vars);
	set_side(vars);
	calc_wall_texture(vars);
	draw_ceailing(vars, img);
	draw_wall(vars, img);
	draw_floor(vars, img);
	vars->zbuffer[vars->render.x] = vars->render.prep_wall_dist;
	vars->render.x++;
}

int		render(t_vars *vars)
{
	t_img img;

	img.img = mlx_new_image(vars->mlx, vars->window.width,
				vars->window.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
	move_player(vars);
	while (vars->render.x < vars->window.width)
		shoot_ray(vars, &img);
	vars->render.x = 0;
	calc_dist_to_sprites(vars);
	sort_sprites(vars, vars->sprite_number);
	display_sprites(vars, &img);
	if (vars->create_image == 1)
	{
		frame_to_bmp(vars, img);
		mlx_destroy_image(vars->mlx, img.img);
		return (1);
	}
	mlx_put_image_to_window(vars->mlx, vars->p_window, img.img, 0, 0);
	mlx_destroy_image(vars->mlx, img.img);
	return (1);
}
