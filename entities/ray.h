/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:03:26 by apavel            #+#    #+#             */
/*   Updated: 2020/07/15 13:06:40 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "../vector/point.h"

typedef struct	s_ray
{
	t_point		pos;
	float		dir;
	float		cos;
	float		sin;

}				t_ray;

#endif