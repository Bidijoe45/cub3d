/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 12:34:41 by apavel            #+#    #+#             */
/*   Updated: 2020/11/06 13:07:17 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_textures_paths(t_parser *parsed_data, t_vars *vars)
{
	vars->texture_north_src = parsed_data->texture_north;
	vars->texture_south_src = parsed_data->texture_south;
	vars->texture_east_src = parsed_data->texture_east;
	vars->texture_west_src = parsed_data->texture_west;
	vars->sprite_texture_src = parsed_data->sprite_texture;
}

void	load_sprite_texture(t_vars *vars)
{
	vars->sprite.img = mlx_xpm_file_to_image(vars->mlx,
		vars->sprite_texture_src, &vars->sprite.width, &vars->sprite.height);
	vars->sprite.addr = mlx_get_data_addr(vars->sprite.img,
		&vars->sprite.bits_per_pixel, &vars->sprite.line_length,
		&vars->sprite.endian);
}

void	load_textures(t_vars *vars)
{
	vars->texture_north.img = mlx_xpm_file_to_image(vars->mlx,
		vars->texture_north_src, &vars->texture_north.width,
		&vars->texture_north.height);
	vars->texture_north.addr = mlx_get_data_addr(vars->texture_north.img,
		&vars->texture_north.bits_per_pixel, &vars->texture_north.line_length,
		&vars->texture_north.endian);
	vars->texture_east.img = mlx_xpm_file_to_image(vars->mlx,
		vars->texture_east_src, &vars->texture_east.width,
		&vars->texture_east.height);
	vars->texture_east.addr = mlx_get_data_addr(vars->texture_east.img,
		&vars->texture_east.bits_per_pixel, &vars->texture_east.line_length,
		&vars->texture_east.endian);
	vars->texture_south.img = mlx_xpm_file_to_image(vars->mlx,
		vars->texture_south_src, &vars->texture_south.width,
		&vars->texture_south.height);
	vars->texture_south.addr = mlx_get_data_addr(vars->texture_south.img,
		&vars->texture_south.bits_per_pixel, &vars->texture_south.line_length,
		&vars->texture_south.endian);
	vars->texture_west.img = mlx_xpm_file_to_image(vars->mlx,
		vars->texture_west_src, &vars->texture_west.width,
		&vars->texture_west.height);
	vars->texture_west.addr = mlx_get_data_addr(vars->texture_west.img,
		&vars->texture_west.bits_per_pixel, &vars->texture_west.line_length,
		&vars->texture_west.endian);
	load_sprite_texture(vars);
}

int		check_textures_files(t_vars *vars)
{
	int file;

	if ((file = open(vars->texture_north_src, O_RDONLY)) == -1)
		return (0);
	close(file);
	if ((file = open(vars->texture_east_src, O_RDONLY)) == -1)
		return (0);
	close(file);
	if ((file = open(vars->texture_south_src, O_RDONLY)) == -1)
		return (0);
	close(file);
	if ((file = open(vars->texture_west_src, O_RDONLY)) == -1)
		return (0);
	close(file);
	if ((file = open(vars->sprite_texture_src, O_RDONLY)) == -1)
		return (0);
	close(file);
	return (1);
}

int		valid_textures(t_vars *vars)
{
	if (vars->texture_north.width <= 0 || vars->texture_north.height <= 0)
		return (0);
	if (vars->texture_south.width <= 0 || vars->texture_south.height <= 0)
		return (0);
	if (vars->texture_east.width <= 0 || vars->texture_east.height <= 0)
		return (0);
	if (vars->texture_west.width <= 0 || vars->texture_west.height <= 0)
		return (0);
	if (vars->sprite.width <= 0 || vars->sprite.height <= 0)
		return (0);
	return (1);
}
