/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:39:19 by apavel            #+#    #+#             */
/*   Updated: 2020/11/06 13:06:34 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int		count_map_size(t_parser *vars, char *str)
{
	int line_size;

	if (!check_variables(vars))
		return (0);
	line_size = ft_strlen(str);
	if (vars->map_width < line_size)
		vars->map_width = line_size;
	vars->map_height++;
	return (1);
}

int		fill_map(t_parser *vars, char *line, int i)
{
	int	j;

	j = 0;
	while (line[j] != '\0')
	{
		if (!ft_strchr(" 012NESW", line[j]))
			return (0);
		if (line[j] == ' ')
			vars->map[i][j] = '0';
		else
			vars->map[i][j] = line[j];
		j++;
	}
	if (!check_player_pos(vars, i, line))
	{
		if (line)
			free(line);
		return (0);
	}
	return (1);
}

int		alloc_map(t_parser *vars)
{
	int i;
	int j;

	if (!(vars->map = malloc(vars->map_height * sizeof(char *))))
		return (0);
	i = 0;
	while (i < vars->map_height)
	{
		j = 0;
		if (!(vars->map[i] = malloc(vars->map_width * sizeof(char))))
			return (0);
		while (j < vars->map_width)
		{
			vars->map[i][j] = '0';
			j++;
		}
		i++;
	}
	return (1);
}

int		nisu(t_parser *vars, char *line, int *i)
{
	int	j;

	j = 0;
	while (ft_isspace(line[j]))
		j++;
	if (ft_isdigit(line[j]))
	{
		if (vars->map_started == 1 && vars->empty_line == 1)
			return (0);
		vars->map_started = 1;
		if (!(fill_map(vars, line, *i)))
			return (0);
		*i += 1;
	}
	else
	{
		if (vars->map_started == 1)
			vars->empty_line = 1;
	}
	return (1);
}

int		parse_map(t_parser *vars, int fd)
{
	char	*line;
	int		ret;
	int		i;

	vars->empty_line = 0;
	if (!alloc_map(vars))
		return (0);
	i = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!nisu(vars, line, &i))
			return (0);
		free(line);
	}
	if (!nisu(vars, line, &i))
		return (0);
	if (line)
		free(line);
	if (vars->player_x == -1 && vars->player_y == -1)
		return (0);
	return (1);
}
