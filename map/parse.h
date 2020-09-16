/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 11:23:55 by apavel            #+#    #+#             */
/*   Updated: 2020/07/13 11:42:10 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int		get_file_size(const char *file_name);
char	*get_file_str(const char *file_name);

#endif