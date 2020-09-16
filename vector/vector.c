/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 13:10:36 by apavel            #+#    #+#             */
/*   Updated: 2020/07/16 09:15:18 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vector_create(t_point start, t_point end)
{
	t_vector vector;

	vector.start = start;
	vector.end = end;
	return (vector);
}

float		vector_length(t_vector vector)
{
	float length;
	
	length = sqrt(pow(vector.end.x - vector.start.x, 2) + pow(vector.end.y - vector.start.y, 2));
	return (length);
}