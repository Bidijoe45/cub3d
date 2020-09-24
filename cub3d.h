/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:02:23 by apavel            #+#    #+#             */
/*   Updated: 2020/09/23 11:24:14 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "map/map.h"
#include "entities/player.h"
#include "render/image.h"

typedef	struct	s_screen
{
	int			width;
	int			height;
}				t_screen;

typedef struct s_srpite
{
	double x;
	double y;
	double distance;
}				t_sprite;

typedef struct	s_vars
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_player	player;
	t_screen	screen;
	t_img		sprite;
	t_img		texture_north;
	t_img		texture_east;
	t_img		texture_south;
	t_img		texture_west;

	t_sprite	*sprite_order;
	int			sprite_number;

	double		*zbuffer;
}				t_vars;

#endif
