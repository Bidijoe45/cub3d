/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:15:29 by apavel            #+#    #+#             */
/*   Updated: 2020/11/04 13:38:25 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

#define BUFFER_SIZE 1000

static int	verify_stack(char **stack, char **line)
{
	char *tmp_str;

	if (ft_strchr(*stack, '\n'))
	{
		*line = ft_substr(*stack, 0, ft_strlen(*stack) -
				ft_strlen(ft_strchr(*stack, '\n')));
		tmp_str = *stack;
		*stack = ft_strdup(ft_strchr(tmp_str, '\n') + 1);
		free(tmp_str);
		return (1);
	}
	else
		return (0);
}

static int	read_line(int fd, char **stack)
{
	char	*buff;
	int		bytes;
	char	*tmp_str;

	if (!(buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((bytes = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[bytes] = '\0';
		if (stack[fd])
		{
			tmp_str = stack[fd];
			stack[fd] = ft_strjoin(tmp_str, buff);
			free(tmp_str);
		}
		else
			stack[fd] = ft_strdup(buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (bytes);
}

int			get_next_line(int fd, char **line)
{
	static char		*stack[4096];
	int				ret;

	if (fd < 0 || read(fd, stack[fd], 0) == -1 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (stack[fd])
		if (verify_stack(&stack[fd], line))
			return (1);
	ret = read_line(fd, stack);
	if (ret == 0 && !stack[fd])
	{
		*line = ft_strdup("");
		return (0);
	}
	if (verify_stack(&stack[fd], line))
		return (1);
	if (!ft_strchr(stack[fd], '\n'))
	{
		*line = ft_strdup(stack[fd]);
		free(stack[fd]);
		stack[fd] = NULL;
		return (0);
	}
	return (0);
}
