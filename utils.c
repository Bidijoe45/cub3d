/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:12:32 by apavel            #+#    #+#             */
/*   Updated: 2020/07/16 09:19:12 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

unsigned int	ft_strlen(const char *str)
{
	unsigned int	len;

	len  = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

float			deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}