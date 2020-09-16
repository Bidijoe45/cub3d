/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 12:44:10 by apavel            #+#    #+#             */
/*   Updated: 2020/09/16 12:36:46 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define map_width 24
#define map_height 24

int map[map_width][map_height]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int render(t_vars *vars)
{	
	t_img img;
	t_ray ray;
	t_wall wall;

	img.img = mlx_new_image(vars->mlx, vars->screen.width, vars->screen.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	for (int x = 0; x < vars->screen.width; x++)
	{
		float camera_x = 2 * x / (double)vars->screen.width - 1;
		float ray_dir_x = vars->player.dir_x + vars->player.plane_x * camera_x;
		float ray_dir_y = vars->player.dir_y + vars->player.plane_y * camera_x;

		int map_x = (int)vars->player.pos_x;
		int map_y = (int)vars->player.pos_y;

		float side_dist_x;
		float side_dist_y;

		float delta_dist_x = (ray_dir_y == 0) ? 0 : ((ray_dir_x == 0) ? 1 : fabs(1 / ray_dir_x));
		float delta_dist_y = (ray_dir_x == 0) ? 0 : ((ray_dir_y == 0) ? 1 : fabs(1 / ray_dir_y));
		float prep_wall_dist;

		int step_x = 0;
		int step_y = 0;

		int hit = 0;
		int side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (vars->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - vars->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (vars->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - vars->player.pos_y) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			
			if (map[map_x][map_y] > 0) hit = 1;
		}

		if (side == 0)
			prep_wall_dist = (map_x - vars->player.pos_x + (1 - step_x) / 2) / ray_dir_x;
      	else
			prep_wall_dist = (map_y - vars->player.pos_y + (1 - step_y) / 2) / ray_dir_y;

		float line_height = (vars->screen.height / prep_wall_dist);
		
		int draw_start = -line_height / 2 + vars->screen.height / 2;
		if (draw_start < 0)
			draw_start = 0;

		int draw_end = line_height / 2 + vars->screen.height / 2;
		if (draw_end >= vars->screen.height)
			draw_end = vars->screen.height - 1;
		
		int color = 0x000000;
		if (map[map_x][map_y] == 1)
			color = 0xff0000;
		if (map[map_x][map_y] == 2)
			color = 0x00ff00;
		if (map[map_x][map_y] == 3)
			color = 0x0000ff;
		if (map[map_x][map_y] == 4)
			color = 0xffffff;
		
		
		if (side == 1)
			color = color / 2;
		

		draw_line(&img, point_create(x, draw_start), point_create(x, draw_end), color);

	}
	
	
	mlx_put_image_to_window(vars->mlx, vars->window, img.img, 0, 0);
	if (img.img)
		mlx_destroy_image(vars->mlx, img.img);
	
	return (1);
}