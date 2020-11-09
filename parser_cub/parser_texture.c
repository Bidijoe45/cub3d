/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:39:33 by apavel            #+#    #+#             */
/*   Updated: 2020/11/04 13:39:34 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int		is_null_texture(t_parser *vars, int type)
{
	if (type == 1)
		return (vars->texture_north != NULL ? 0 : 1);
	else if (type == 2)
		return (vars->texture_south != NULL ? 0 : 1);
	else if (type == 3)
		return (vars->texture_east != NULL ? 0 : 1);
	else if (type == 4)
		return (vars->texture_west != NULL ? 0 : 1);
	else
		return (vars->sprite_texture != NULL ? 0 : 1);
}

int		save_texture_dir(t_parser *vars, int type, char *str)
{
	if (!is_null_texture(vars, type))
		return (0);
	if (type == 1)
		vars->texture_north = ft_strdup(str);
	else if (type == 2)
		vars->texture_south = ft_strdup(str);
	else if (type == 3)
		vars->texture_east = ft_strdup(str);
	else if (type == 4)
		vars->texture_west = ft_strdup(str);
	else
		vars->sprite_texture = ft_strdup(str);
	return (1);
}

int		parse_texture_line(t_parser *vars, int type, char *str)
{
	int i;

	i = (type == 5) ? 1 : 2;
	if (!ft_isspace(str[i]))
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isascii(str[i]))
		return (0);
	if (!save_texture_dir(vars, type, &str[i]))
		return (0);
	return (1);
}
