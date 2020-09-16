/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:02:23 by apavel            #+#    #+#             */
/*   Updated: 2020/09/15 09:58:07 by apavel           ###   ########.fr       */
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

typedef struct	s_sprite
{
	t_point 	pos;
	float		dist;
	float		dir;
	float		size;
}				t_sprite;

typedef struct	s_vars
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_player	player;
	t_screen	screen;
	t_img		texture_north;
	t_img		texture_east;
	t_img		texture_south;
	t_img		texture_west;
}				t_vars;

#endif
