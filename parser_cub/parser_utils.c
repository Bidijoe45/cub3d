/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:39:38 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 11:59:52 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int		check_file_name(const char *str)
{
	int		i;
	char	dot;
	int		bd_chars;

	i = 0;
	dot = 0;
	bd_chars = 0;
	while (str[i] != '\0' || dot == 0)
	{
		if (str[i] == '.')
			dot = 1;
		if (dot == 0)
			bd_chars++;
		i++;
	}
	if (dot == 1 && str[i] == 'c' && str[i + 1] == 'u' && str[i] == 'b')
		return (1);
	return (0);
}

int		empty_end_of_line(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	flood_fill(t_parser *vars, int x, int y, int prev_color)
{
	if (x < 0 || x >= vars->map_width || y < 0 || y >= vars->map_height)
		return ;
	if (vars->map[y][x] != prev_color && vars->map[y][x] != '2')
		return ;
	if (vars->map[y][x] == '0')
		vars->map[y][x] = '9';
	else if (vars->map[y][x] == '2')
		vars->map[y][x] = '8';
	flood_fill(vars, x + 1, y, prev_color);
	flood_fill(vars, x - 1, y, prev_color);
	flood_fill(vars, x, y + 1, prev_color);
	flood_fill(vars, x, y - 1, prev_color);
}

int		check_player_pos(t_parser *vars, int y, char *str)
{
	int x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == 'N')
			vars->player_dir = 90;
		else if (str[x] == 'S')
			vars->player_dir = 270;
		else if (str[x] == 'E')
			vars->player_dir = 0;
		else if (str[x] == 'W')
			vars->player_dir = 180;
		if (ft_strchr("NESW", str[x]))
		{
			if (vars->player_x != -1 || vars->player_y != -1)
				return (0);
			vars->player_x = x;
			vars->player_y = y;
			vars->map[y][x] = '0';
		}
		x++;
	}
	return (1);
}

void	convert_map(t_parser *vars)
{
	int i;
	int j;

	i = 0;
	while (i < vars->map_height)
	{
		j = 0;
		while (j < vars->map_width)
		{
			if (vars->map[i][j] == '9')
				vars->map[i][j] = '0';
			j++;
		}
		i++;
	}
}
