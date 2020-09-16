/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 10:55:33 by apavel            #+#    #+#             */
/*   Updated: 2020/07/14 10:10:49 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include "../utils.h"
#include "parse.h"

typedef struct	s_map
{
	int			width;
	int			height;
	char		**str;
}				t_map;

t_map			parse_map();
int				is_empty();

#endif
