/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:00:51 by apavel            #+#    #+#             */
/*   Updated: 2020/09/24 11:55:43 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <mlx.h>
#include "../cub3d.h"
#include "../entities/ray.h"
#include "../vector/point.h"
#include "../vector/vector.h"
#include "draw.h"
#include "image.h"
#include "../entities/wall.h"
#include "../vector/point.h"

int		render(t_vars *vars);
int		key_handler(int keycode, t_vars *vars);

#endif
