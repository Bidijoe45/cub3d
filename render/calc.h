/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:33:33 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 12:10:36 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "../cub3d.h"

void	calc_ray_dir(t_vars *vars);
void	calc_delta_dist(t_vars *vars);
void	calc_side_dist(t_vars *vars);
void	calc_wall_texture(t_vars *vars);
void	calc_dist_to_sprites(t_vars *vars);

#endif
