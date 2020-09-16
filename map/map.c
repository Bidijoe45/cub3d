/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:20:51 by apavel            #+#    #+#             */
/*   Updated: 2020/07/14 10:18:20 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

char	*get_map_str()
{
	char 	*file_str;
	int		map_finded;
	char	*map_str;
	int		i;
	int		j;

	file_str = get_file_str("cub.conf");
	map_finded = 0;
	i = 0;
	while (file_str[i] != '\0' && map_finded == 0)
	{
		if (file_str[i] == '1' && file_str[i - 1] == '\n')
		{
			map_finded = 1;
			break;
		}
		i++;
	}
	map_str = malloc(ft_strlen(&file_str[i]) + 1);
	j = 0;
	while (file_str[i] != '\0')
		map_str[j++] = file_str[i++];
	map_str[j] = '\0';
	free(file_str);
	return (map_str);
}

t_map	parse_map()
{
	t_map map;

	map.width = 10;
	map.height = 10;


	return (map);
}

int		is_empty(t_map map, int x, int y)
{	
	if (map.str[y][x] == 0)
		return 1;
	else
		return 0;
}