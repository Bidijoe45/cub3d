#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "cub3d.h"
#include "vector/point.h"
#include "render/render.h"
#include "libft/libft.h"

#include "./parser_cub/file.h"


int close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->p_window);
	exit(0);
}

int	key_release_handler(int keycode, t_vars *vars)
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

int	key_press_handler(int keycode, t_vars *vars)
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

unsigned long   create_rgb(int r, int g, int b)
{
    return (r << 16) + (g << 8) + b;
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

void	check_window_resolution(t_vars *vars)
{
	if (vars->window.width > 2432)
		vars->window.width = 2432;
	if (vars->window.height > 1368)
		vars->window.height = 1368;
}

void	load_sprite_texture(t_vars *vars)
{		
	vars->sprite.img = mlx_xpm_file_to_image(vars->mlx,
		vars->sprite_texture_src, &vars->sprite.width, &vars->sprite.heigth);
	vars->sprite.addr = mlx_get_data_addr(vars->sprite.img,
		&vars->sprite.bits_per_pixel, &vars->sprite.line_length,
		&vars->sprite.endian);
}

void	load_textures(t_vars *vars)
{
	vars->texture_north.img = mlx_xpm_file_to_image(vars->mlx,
		vars->texture_north_src, &vars->texture_north.width,
		&vars->texture_north.heigth);
	vars->texture_north.addr = mlx_get_data_addr(vars->texture_north.img,
		&vars->texture_north.bits_per_pixel, &vars->texture_north.line_length,
		&vars->texture_north.endian);
	vars->texture_east.img = mlx_xpm_file_to_image(vars->mlx,
		vars->texture_east_src, &vars->texture_east.width,
		&vars->texture_east.heigth);
	vars->texture_east.addr = mlx_get_data_addr(vars->texture_east.img,
		&vars->texture_east.bits_per_pixel, &vars->texture_east.line_length,
		&vars->texture_east.endian);
	vars->texture_south.img = mlx_xpm_file_to_image(vars->mlx,
		vars->texture_south_src, &vars->texture_south.width,
		&vars->texture_south.heigth);
	vars->texture_south.addr = mlx_get_data_addr(vars->texture_south.img,
		&vars->texture_south.bits_per_pixel, &vars->texture_south.line_length,
		&vars->texture_south.endian);
	vars->texture_west.img = mlx_xpm_file_to_image(vars->mlx,
		vars->texture_west_src, &vars->texture_west.width,
		&vars->texture_west.heigth);
	vars->texture_west.addr = mlx_get_data_addr(vars->texture_west.img,
		&vars->texture_west.bits_per_pixel, &vars->texture_west.line_length,
		&vars->texture_west.endian);
	load_sprite_texture(vars);
}

void	init_player_dir(t_vars *vars)
{
	vars->player.dir_x = 0;
	vars->player.dir_y = 0;
	vars->player.plane_x = 0;
	vars->player.plane_y = 0;
}

void	set_player_dir(t_vars *vars, int player_dir)
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

void	init_map(t_parser *parsed_data, t_vars *vars)
{
	vars->map.height = parsed_data->map_height;
	vars->map.width = parsed_data->map_width;
	vars->map.map = parsed_data->map;
}

void	set_textures_paths(t_parser *parsed_data, t_vars *vars)
{
	vars->texture_north_src = parsed_data->texture_north;
	vars->texture_south_src = parsed_data->texture_south;
	vars->texture_east_src = parsed_data->texture_east;
	vars->texture_west_src = parsed_data->texture_west;
	vars->sprite_texture_src = parsed_data->sprite_texture;
}

void init_player(t_parser *parsed_data, t_vars *vars)
{
	vars->player.pos_x = parsed_data->player_y + 0.5;
	vars->player.pos_y = parsed_data->player_x + 0.5;
	set_player_dir(vars, parsed_data->player_dir);
	vars->player.speed = 0.07;
	vars->player.rot_speed = 0.05;
}

void	init_render_data(t_vars *vars)
{
	vars->data.map_x = 0;
	vars->data.map_y = 0;
	vars->data.step_x = 0;
	vars->data.step_y = 0;
	vars->data.hit = 0;
	vars->data.side = 0;
	vars->data.draw_start = 0;
	vars->data.draw_end = 0;
	vars->data.camera_x = 0;
	vars->data.ray_dir_x = 0;
	vars->data.ray_dir_y = 0;
	vars->data.side_dist_x = 0;
	vars->data.side_dist_y = 0;
	vars->data.delta_dist_x = 0;
	vars->data.delta_dist_y = 0;
	vars->data.prep_wall_dist = 0;
	vars->data.line_height = 0;
}

int	init_vars(t_parser *parsed_data, t_vars *vars)
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
	vars->cealing_color = create_rgb(parsed_data->c_c[0], parsed_data->c_c[1], parsed_data->c_c[2]);
	vars->floor_color = create_rgb(parsed_data->f_c[0], parsed_data->f_c[1], parsed_data->f_c[2]);
	set_textures_paths(parsed_data, vars);
	if (check_textures_files(vars) == 0)
		return (0);
	load_textures(vars);
	vars->p_window = mlx_new_window(vars->mlx, vars->window.width, vars->window.height, "cub3d");
	vars->zbuffer = malloc(sizeof(double) * vars->window.width);
	init_render_data(vars);
	return (1);
}

int	check_args(t_vars *vars, int argc, char **argv)
{
	if (argc == 2)
		return (0);
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 7) == 0)
	{
		vars->create_image = 1;
		return (1);
	}
	return (-1);
}

void	create_hooks(t_vars *vars)
{
	mlx_hook(vars->p_window, 2, 0L, key_press_handler, vars);
	mlx_hook(vars->p_window, 3, 0L, key_release_handler, vars);
	mlx_hook(vars->p_window, 17, 0L, close_window, vars);
	mlx_loop_hook(vars->mlx, render, vars);
	mlx_loop(vars->mlx);
}

int	main(int argc, char **argv)
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
		return(0);
	}
	if (read_file(parsed_data, argv[1]) == 0 || init_vars(parsed_data, vars) == 0)
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
