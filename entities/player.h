/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:56:16 by apavel            #+#    #+#             */
/*   Updated: 2020/09/15 12:35:16 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

#include "../vector/point.h"

typedef struct	s_player
{
	t_point		pos;
	float		dir;
	float		speed;
	float		rotation_amount;
	float		fov;
	float		cos;
	float		sin;
//------------------------------
	float		pos_x;
	float		pos_y;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
	float		rot_speed;
}				t_player;

#endif
