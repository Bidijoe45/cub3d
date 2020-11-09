/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:39:04 by apavel            #+#    #+#             */
/*   Updated: 2020/11/04 13:39:07 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int		valid_colors(t_parser *vars, int type)
{
	if (type == 1 && vars->c_c[0] >= 0
		&& vars->c_c[0] <= 255
		&& vars->c_c[1] >= 0 && vars->c_c[1] <= 255
		&& vars->c_c[2] >= 0 && vars->c_c[2] <= 255)
		return (1);
	if (type == 2 && vars->f_c[0] >= 0 && vars->f_c[0] <= 255
		&& vars->f_c[1] >= 0 && vars->f_c[1] <= 255
		&& vars->f_c[2] >= 0 && vars->f_c[2] <= 255)
		return (1);
	return (0);
}

int		save_color(t_parser *vars, int type, int color, char *str)
{
	if (!ft_isdigit(str[0]))
		return (0);
	if (type == 1)
	{
		if (vars->c_c[0] != -1 && vars->c_c[1] != -1 && vars->c_c[2] != -1)
			return (0);
		if (color == 0)
			vars->c_c[0] = ft_atoi(str);
		else if (color == 1)
			vars->c_c[1] = ft_atoi(str);
		else
			vars->c_c[2] = ft_atoi(str);
	}
	else
	{
		if (vars->f_c[0] != -1 && vars->f_c[1] != -1 && vars->f_c[2] != -1)
			return (0);
		if (color == 0)
			vars->f_c[0] = ft_atoi(str);
		else if (color == 1)
			vars->f_c[1] = ft_atoi(str);
		else
			vars->f_c[2] = ft_atoi(str);
	}
	return (1);
}

int		parse_color_line(t_parser *vars, int type, char *str)
{
	int i;
	int	j;

	i = 1;
	if (!ft_isspace(str[i]))
		return (0);
	while (ft_isspace(str[i]))
		i++;
	j = 0;
	while (j < 3)
	{
		if (!save_color(vars, type, j, &str[i]))
			return (0);
		while (ft_isdigit(str[i]))
			i++;
		if (j != 2 && str[i] != ',')
			return (0);
		if (str[i] == ',')
			i++;
		j++;
	}
	if (!empty_end_of_line(&str[i]))
		return (0);
	return (valid_colors(vars, type) == 0 ? 0 : 1);
}
