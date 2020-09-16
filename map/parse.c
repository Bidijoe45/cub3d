/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:25:01 by apavel            #+#    #+#             */
/*   Updated: 2020/07/16 09:39:37 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int		get_file_size(const char *file_name)
{
	int		file;
	int		file_size;
	char	buff;

	file_size = 0;
	file = open(file_name, O_RDONLY);
	while (read(file, &buff, 1) != 0)
		file_size++;
	return (file_size);
}

char	*get_file_str(const char *file_name)
{
	int		file;
	int		file_size;
	char	*file_str;
	
	file = open(file_name, O_RDONLY);
	file_size = get_file_size(file_name);
	file_str = malloc(sizeof(char) * file_size + 1);
	read(file, file_str, file_size);
	file_str[file_size] = '\0';
	return (file_str);
}