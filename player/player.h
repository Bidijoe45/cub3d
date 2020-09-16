/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:56:16 by apavel            #+#    #+#             */
/*   Updated: 2020/07/13 11:10:04 by apavel           ###   ########.fr       */
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
}				t_player;

#endif
