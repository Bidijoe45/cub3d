/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:39:13 by apavel            #+#    #+#             */
/*   Updated: 2020/11/06 13:06:20 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int		detect_textures_type(t_parser *vars, char *str)
{
	int	i;

	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O')
		return (parse_texture_line(vars, 1, &str[i]));
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (parse_texture_line(vars, 2, &str[i]));
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (parse_texture_line(vars, 3, &str[i]));
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (parse_texture_line(vars, 4, &str[i]));
	else if (str[i] == 'S')
		return (parse_texture_line(vars, 5, &str[i]));
	return (0);
}

int		detect_line_type(t_parser *vars, char *str)
{
	int i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	if (str[i] == 'R')
		return (parse_resolution_line(vars, &str[i]));
	if (ft_strchr("NSEW", str[i]))
		return (detect_textures_type(vars, &str[i]));
	else if (str[i] == 'C')
		return (parse_color_line(vars, 1, &str[i]));
	else if (str[i] == 'F')
		return (parse_color_line(vars, 2, &str[i]));
	else if (ft_strchr("012", str[i]) || ft_isspace(str[i]))
		return (count_map_size(vars, str));
	return (0);
}

int		check_file(t_parser *vars, int fd)
{
	char	*line;
	int		ret;
	int		correct_line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		correct_line = detect_line_type(vars, line);
		free(line);
		if (correct_line == 0)
			return (0);
	}
	correct_line = detect_line_type(vars, line);
	free(line);
	if (correct_line == 0)
		return (0);
	if (vars->map_height < 4 || vars->map_width < 4)
		return (0);
	return (1);
}

int		check_map(t_parser *vars)
{
	int i;

	i = 0;
	while (i < vars->map_width)
	{
		if (vars->map[0][i] == '9'
			|| vars->map[vars->map_height - 1][i] == '9')
			return (0);
		i++;
	}
	i = 0;
	while (i < vars->map_height)
	{
		if (vars->map[i][0] == '9'
			|| vars->map[i][vars->map_width - 1] == '9')
			return (0);
		i++;
	}
	return (1);
}

int		read_file(t_parser *vars, const char *file_name)
{
	int fd;
	int	map_ok;

	initialize_vars(vars);
	if (check_file_name(file_name) == -1)
		return (0);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	if (!check_file(vars, fd))
		return (0);
	close(fd);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	if (!parse_map(vars, fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	flood_fill(vars, vars->player_x, vars->player_y, '0');
	map_ok = check_map(vars);
	detect_sprites(vars);
	convert_map(vars);
	return (map_ok == 1) ? 1 : 0;
}
