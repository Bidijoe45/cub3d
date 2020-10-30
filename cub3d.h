/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:02:23 by apavel            #+#    #+#             */
/*   Updated: 2020/10/30 13:40:37 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <fcntl.h>
#include <unistd.h>
#include "entities/player.h"
#include "render/image.h"
#include "entities/sprite.h"
#include "libft/libft.h"

typedef	struct	s_keys
{
	char		larrow_key;
	char		rarrow_key;
	char		w_key;
	char		s_key;
	char		a_key;
	char		d_key;
}				t_keys;

typedef	struct	s_window
{
	int			width;
	int			height;
}				t_window;

typedef	struct	s_map
{
	int			width;
	int			height;
	char		**map;
}				t_map;

typedef struct	s_render
{
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			draw_start;
	int			draw_end;
	float		camera_x;
	float		ray_dir_x;
	float		ray_dir_y;
	float		side_dist_x;
	float		side_dist_y;
	float		delta_dist_x;
	float		delta_dist_y;
	float		prep_wall_dist;
	float		line_height;
}				t_render;

typedef struct	s_vars
{
	void		*mlx;
	void		*p_window;
	t_keys		keys;
	t_player	player;
	t_window	window;
	t_img		sprite;
	t_map		map;
	char		*texture_north_src;
	char		*texture_east_src;
	char		*texture_south_src;
	char		*texture_west_src;
	char		*sprite_texture_src;
	t_img		texture_north;
	t_img		texture_east;
	t_img		texture_south;
	t_img		texture_west;
	unsigned int	cealing_color;
	unsigned int	floor_color;
	
	t_sprite	*sprite_order;
	int			sprite_number;

	double		*zbuffer;

	int			create_image;
	t_render	data;
}				t_vars;




#endif
