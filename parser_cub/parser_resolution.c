/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:39:23 by apavel            #+#    #+#             */
/*   Updated: 2020/11/04 13:39:24 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int		parse_resolution_line(t_parser *vars, char *str)
{
	int i;

	i = 1;
	if (vars->w_width != -1 || vars->w_height != -1 || !ft_isspace(str[i]))
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	vars->w_width = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	vars->w_height = ft_atoi(&str[i]);
	while (ft_isdigit(str[i]))
		i++;
	if (!empty_end_of_line(&str[i]))
		return (0);
	return (1);
}
