/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:02:23 by apavel            #+#    #+#             */
/*   Updated: 2020/11/09 10:53:04 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "./render/image.h"
# include "./entities/player.h"
# include "./entities/sprite.h"
# include "./libft/libft.h"
# include "./parser_cub/file.h"

typedef	struct		s_keys
{
	char			larrow_key;
	char			rarrow_key;
	char			w_key;
	char			s_key;
	char			a_key;
	char			d_key;
}					t_keys;

typedef	struct		s_window
{
	int				width;
	int				height;
}					t_window;

typedef	struct		s_map
{
	int				width;
	int				height;
	char			**map;
}					t_map;

typedef struct		s_render
{
	int				i;
	int				x;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				draw_start;
	int				draw_end;
	int				color;
	int				tex_x;
	float			camera_x;
	float			ray_dir_x;
	float			ray_dir_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			prep_wall_dist;
	float			line_height;
	float			wall_x;
	float			step;
	float			tex_pos;
}					t_render;

typedef struct		s_render_sprite
{
	int				sprite_screen_x;
	int				height;
	int				draw_start_y;
	int				draw_end_y;
	int				width;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	int				tex_y;
	int				color;
	float			x;
	float			y;
	float			inv_det;
	float			transform_x;
	float			transform_y;
}					t_render_sprite;

typedef struct		s_vars
{
	char			*texture_north_src;
	char			*texture_east_src;
	char			*texture_south_src;
	char			*texture_west_src;
	char			*sprite_texture_src;
	void			*mlx;
	void			*p_window;
	unsigned int	cealing_color;
	unsigned int	floor_color;
	int				sprite_number;
	float			*zbuffer;
	int				create_image;
	t_keys			keys;
	t_player		player;
	t_window		window;
	t_map			map;
	t_img			sprite;
	t_img			texture_north;
	t_img			texture_east;
	t_img			texture_south;
	t_img			texture_west;
	t_sprite		*sprite_order;
	t_render		render;
}					t_vars;

int					render(t_vars *vars);
int					key_handler(int keycode, t_vars *vars);
void				move_player(t_vars *vars);
void				sort_sprites(t_vars *vars, int n);
void				display_sprites(t_vars *vars, t_img *img);
void				rotate_left(t_vars *vars);
void				rotate_right(t_vars *vars);
void				set_textures_paths(t_parser *parsed_data, t_vars *vars);
void				load_sprite_texture(t_vars *vars);
void				load_textures(t_vars *vars);
int					check_textures_files(t_vars *vars);
int					init_vars(t_parser *parsed_data, t_vars *vars);
void				create_hooks(t_vars *vars);
int					valid_textures(t_vars *vars);
void				init_player_dir(t_vars *vars);
void				set_player_dir(t_vars *vars, int player_dir);
void				check_window_resolution(t_vars *vars);
unsigned long		create_rgb(int r, int g, int b);
int					valid_textures(t_vars *vars);

#endif
