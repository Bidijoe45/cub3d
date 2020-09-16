/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:02:00 by apavel            #+#    #+#             */
/*   Updated: 2020/07/16 09:13:45 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include "point.h"

typedef struct	s_vector
{
	t_point		start;
	t_point		end;		
}				t_vector;

t_vector		vector_create(t_point start, t_point end);
float			vector_length(t_vector vector);

#endif