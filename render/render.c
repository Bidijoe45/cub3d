/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 12:44:10 by apavel            #+#    #+#             */
/*   Updated: 2020/10/30 14:01:05 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int texture_width = 64;
int texture_height = 64;

void	frame_to_bmp(t_vars *vars, t_img img)
{	
	int file;
	unsigned char bmpfileheader[14];
	unsigned char bmpinfoheader[40];
	
	ft_bzero(bmpfileheader, 14);
	ft_bzero(bmpinfoheader, 40);

	int filesize = 54 + vars->window.width * vars->window.height * img.bits_per_pixel / 8;
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize>>8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);
	bmpfileheader[10] = 54;

	bmpinfoheader[0] = 40;
	bmpinfoheader[ 4] = (unsigned char)(vars->window.width);
	bmpinfoheader[ 5] = (unsigned char)(vars->window.width>>8);
	bmpinfoheader[ 6] = (unsigned char)(vars->window.width>>16);
	bmpinfoheader[ 7] = (unsigned char)(vars->window.width>>24);
	bmpinfoheader[ 8] = (unsigned char)(vars->window.height);
	bmpinfoheader[ 9] = (unsigned char)(vars->window.height>> 8);
	bmpinfoheader[10] = (unsigned char)(vars->window.height>>16);
	bmpinfoheader[11] = (unsigned char)(vars->window.height>>24);
	bmpinfoheader[12] = 1;
	bmpinfoheader[14] = img.bits_per_pixel;

	file = open("./foto.bmp", O_WRONLY | O_CREAT, 0777);

	write(file, bmpfileheader, 14);
	write(file, bmpinfoheader, 40);

	unsigned int *addr = (unsigned int *)img.addr;

	for (int i=vars->window.height - 1; i >= 0; i--)
	{
		for (int j=0; j < vars->window.width; j++)
		{
			write(file, &addr[i * vars->window.width + j], 4);
		}
	}
	
	close(file);
}

void	move_forward(t_vars *vars)
{
	if(vars->map.map[(int)(vars->player.pos_x + vars->player.dir_x * vars->player.speed)][(int)vars->player.pos_y] == '0') vars->player.pos_x += vars->player.dir_x * vars->player.speed;
    if(vars->map.map[(int)vars->player.pos_x][(int)(vars->player.pos_y + vars->player.dir_y * vars->player.speed)] == '0') vars->player.pos_y += vars->player.dir_y * vars->player.speed;
}

void	move_backward(t_vars *vars)
{
	if(vars->map.map[(int)(vars->player.pos_x - vars->player.dir_x * vars->player.speed)][(int)vars->player.pos_y] == '0') vars->player.pos_x -= vars->player.dir_x * vars->player.speed;
    if(vars->map.map[(int)vars->player.pos_x][(int)(vars->player.pos_y - vars->player.dir_y * vars->player.speed)] == '0') vars->player.pos_y -= vars->player.dir_y * vars->player.speed;
}

void	move_left(t_vars *vars)
{	
	if(vars->map.map[(int)(vars->player.pos_x + (vars->player.dir_y * -1) * vars->player.speed)][(int)vars->player.pos_y] == '0') vars->player.pos_x += (vars->player.dir_y * -1) * vars->player.speed;
	if(vars->map.map[(int)vars->player.pos_x][(int)(vars->player.pos_y + vars->player.dir_x * vars->player.speed)] == '0') vars->player.pos_y += vars->player.dir_x * vars->player.speed;
}

void	move_right(t_vars *vars)
{
	if(vars->map.map[(int)(vars->player.pos_x + vars->player.dir_y * vars->player.speed)][(int)vars->player.pos_y] == '0') vars->player.pos_x += (vars->player.dir_y) * vars->player.speed;
    if(vars->map.map[(int)vars->player.pos_x][(int)(vars->player.pos_y + (vars->player.dir_x * -1) * vars->player.speed)] == '0') vars->player.pos_y += (vars->player.dir_x * -1) * vars->player.speed;
}

void	rotate_left(t_vars *vars)
{
	double old_dir_x = vars->player.dir_x;
	vars->player.dir_x = vars->player.dir_x * cos(vars->player.rot_speed) - vars->player.dir_y * sin(vars->player.rot_speed);
	vars->player.dir_y = old_dir_x * sin(vars->player.rot_speed) + vars->player.dir_y * cos(vars->player.rot_speed);
	double oldPlaneX = vars->player.plane_x;
	vars->player.plane_x = vars->player.plane_x * cos(vars->player.rot_speed) - vars->player.plane_y * sin(vars->player.rot_speed);
	vars->player.plane_y = oldPlaneX * sin(vars->player.rot_speed) + vars->player.plane_y * cos(vars->player.rot_speed);
}

void	rotate_right(t_vars *vars)
{
	double old_dir_x = vars->player.dir_x;
	vars->player.dir_x = vars->player.dir_x * cos(-(vars->player.rot_speed)) - vars->player.dir_y * sin(-(vars->player.rot_speed));
	vars->player.dir_y = old_dir_x * sin(-(vars->player.rot_speed)) + vars->player.dir_y * cos(-(vars->player.rot_speed));
	double oldPlaneX = vars->player.plane_x;
	vars->player.plane_x = vars->player.plane_x * cos(-(vars->player.rot_speed)) - vars->player.plane_y * sin(-(vars->player.rot_speed));
	vars->player.plane_y = oldPlaneX * sin(-(vars->player.rot_speed)) + vars->player.plane_y * cos(-(vars->player.rot_speed));
}

void	move_player(t_vars *vars)
{
	if (vars->keys.w_key == 1)
		move_forward(vars);
	if (vars->keys.s_key == 1)
		move_backward(vars);
	if (vars->keys.a_key == 1)
		move_left(vars);
	if (vars->keys.d_key == 1)
		move_right(vars);
	if (vars->keys.larrow_key == 1)
		rotate_left(vars);
	if (vars->keys.rarrow_key == 1)
		rotate_right(vars);
}

void swap(t_sprite *xp, t_sprite *yp) 
{ 
    t_sprite temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
}

void sort_sprites(t_vars *vars, int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)
	{
		for (j = 0; j < n-i-1; j++) 
		{
        	if (vars->sprite_order[j].distance <= vars->sprite_order[j+1].distance)  
            	swap(&vars->sprite_order[j], &vars->sprite_order[j+1]); 
		}
	}      
}

int render(t_vars *vars)
{	
	t_img img;
	t_ray ray;
	t_wall		wall;

	img.img = mlx_new_image(vars->mlx, vars->window.width, vars->window.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	move_player(vars);

	for (int x = 0; x < vars->window.width; x++)
	{
		float camera_x = 2 * x / (double)vars->window.width - 1;
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
			if (vars->map.map[map_x][map_y] == '1') hit = 1;
		}

		if (side == 0)
			prep_wall_dist = (map_x - vars->player.pos_x + (1 - step_x) / 2) / ray_dir_x;
      	else
			prep_wall_dist = (map_y - vars->player.pos_y + (1 - step_y) / 2) / ray_dir_y;

		float line_height = (vars->window.height / prep_wall_dist);
		
		int draw_start = -line_height / 2 + vars->window.height / 2;
		if (draw_start < 0)
			draw_start = 0;

		int draw_end = line_height / 2 + vars->window.height / 2;
		if (draw_end >= vars->window.height)
			draw_end = vars->window.height - 1;
		
		int color = 0x000000;
	
		float wall_x;
		if (side == 0)
			wall_x = vars->player.pos_y + prep_wall_dist * ray_dir_y;
		else
			wall_x = vars->player.pos_x + prep_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * (float)texture_width);
		if (side == 0 && ray_dir_x > 0)
			tex_x = texture_width - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)
			tex_x = texture_width - tex_x - 1;
		
		float step = 1 * texture_height / line_height;
		float tex_pos = (draw_start - vars->window.height / 2 + line_height / 2) * step;

		//Draw cealing
		int i = 0;
		while (i < draw_start)
		{
			pixel_put(&img, x, i, vars->cealing_color);
			i++;
		}

		//Draw wall
		for (int y = draw_start; y < draw_end; y++)
		{
			int texY = (int)tex_pos;
			tex_pos += step;
			if (step_x == -1 && side == 0)
				color = ((int *)vars->texture_north.addr)[vars->texture_north.width * texY + tex_x];
			if (step_x == 1 && side == 0)
				color = ((int *)vars->texture_east.addr)[vars->texture_east.width * texY + tex_x];
			if (step_y == -1 && side == 1)
				color = ((int *)vars->texture_south.addr)[vars->texture_south.width * texY + tex_x];
			if (step_y == 1 && side == 1)
				color = ((int *)vars->texture_west.addr)[vars->texture_west.width * texY + tex_x];
			pixel_put(&img, x, y, color);
		}
		//Draw floor
		i = draw_end;
		while (i < vars->window.height)
		{
			pixel_put(&img, x, i, vars->floor_color);
			i++;
		}

		vars->zbuffer[x] = prep_wall_dist;
	}
	

	for(int i = 0; i < vars->sprite_number; i++)
      vars->sprite_order[i].distance = ((vars->player.pos_x - vars->sprite_order[i].x) * (vars->player.pos_x -  vars->sprite_order[i].x) + (vars->player.pos_y - vars->sprite_order[i].y) * (vars->player.pos_y - vars->sprite_order[i].y));
	sort_sprites(vars, vars->sprite_number);
    
    for(int i = 0; i < vars->sprite_number; i++)
    {
      
      double spriteX = vars->sprite_order[i].x - vars->player.pos_x;
      double spriteY = vars->sprite_order[i].y - vars->player.pos_y;

      double invDet = 1.0 / (vars->player.plane_x * vars->player.dir_y - vars->player.dir_x * vars->player.plane_y);

      double transformX = invDet * (vars->player.dir_y * spriteX - vars->player.dir_x * spriteY);
      double transformY = invDet * (-vars->player.plane_y * spriteX + vars->player.plane_x * spriteY);

      int spriteScreenX = (int)((vars->window.width / 2) * (1 + transformX / transformY));

 
      int spriteHeight = abs((int)(vars->window.height / (transformY))); 
     
      int drawStartY = -spriteHeight / 2 + vars->window.height / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + vars->window.height / 2;
      if(drawEndY >= vars->window.height) drawEndY = vars->window.height - 1;

      
      int spriteWidth = abs( (int)(vars->window.height / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= vars->window.width) drawEndX = vars->window.width - 1;

      
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * vars->sprite.width / spriteWidth) / 256;
        
        if(transformY > 0 && stripe > 0 && stripe < vars->window.width && transformY < vars->zbuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) 
        {
          int d = (y) * 256 - vars->window.height * 128 + spriteHeight * 128;
          int texY = ((d * vars->sprite.heigth) / spriteHeight) / 256;
          int color = ((int *)vars->sprite.addr)[vars->sprite.width * texY + texX];
		  if (color != 0x000000)
          pixel_put(&img, stripe, y, color);
        }
      }
    }


	//Save image if arg is --save
	if (vars->create_image == 1)
	{
		frame_to_bmp(vars, img);
		mlx_destroy_image(vars->mlx, img.img);
		return (1);
	}

	mlx_put_image_to_window(vars->mlx, vars->p_window, img.img, 0, 0);
	mlx_destroy_image(vars->mlx, img.img);
	return (1);
}

