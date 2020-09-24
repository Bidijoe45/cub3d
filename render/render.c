/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 12:44:10 by apavel            #+#    #+#             */
/*   Updated: 2020/09/24 10:41:18 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#define map_width 24
#define map_height 24

int texture_width = 64;
int texture_height = 64;

int map[10][10]=
{
  {1,1,1,1,1,1,1,1,1,1},
  {1,1,0,0,0,0,0,0,1,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,1,1,0,1,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,0,1},
  {1,0,0,0,1,0,0,0,1,1},
  {1,1,1,1,1,1,1,1,1,1},
};

int texture[12][12] = 
{
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};


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
	t_wall wall;

	img.img = mlx_new_image(vars->mlx, vars->screen.width, vars->screen.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	for (int x = 0; x < vars->screen.width; x++)
	{
		float camera_x = 2 * x / (double)vars->screen.width - 1;
		float ray_dir_x = vars->player.dir_x + vars->player.plane_x * camera_x;
		float ray_dir_y = vars->player.dir_y + vars->player.plane_y * camera_x;

		printf("ray_dir: %f, %f\n", ray_dir_x, ray_dir_y);

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
		if (step_x == -1 && side == 0)
			color = 0xff0000;
		if (step_x == 1 && side == 0)
			color = 0x00ff00;
		if (step_y == -1 && side == 1)
			color = 0x0000ff;
		if (step_y == 1 && side == 1)
			color = 0xffffff;

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
		float tex_pos = (draw_start - vars->screen.height / 2 + line_height / 2) * step;
		for (int y = draw_start; y < draw_end; y++)
		{
			int texY = (int)tex_pos;
			tex_pos += step;
			//color = ((int *)vars->texture_north.addr)[vars->texture_north.width * texY + tex_x];
			pixel_put(&img, x, y, color);
		}

		vars->zbuffer[x] = prep_wall_dist;
	}
	
	for(int i = 0; i < vars->sprite_number; i++)
      vars->sprite_order[i].distance = ((vars->player.pos_x - vars->sprite_order[i].x) * (vars->player.pos_x -  vars->sprite_order[i].x) + (vars->player.pos_y - vars->sprite_order[i].y) * (vars->player.pos_y - vars->sprite_order[i].y));
	sort_sprites(vars, vars->sprite_number);
	
	
    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < vars->sprite_number; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = vars->sprite_order[i].x - vars->player.pos_x;
      double spriteY = vars->sprite_order[i].y - vars->player.pos_y;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (vars->player.plane_x * vars->player.dir_y - vars->player.dir_x * vars->player.plane_y); //required for correct matrix multiplication

      double transformX = invDet * (vars->player.dir_y * spriteX - vars->player.dir_x * spriteY);
      double transformY = invDet * (-vars->player.plane_y * spriteX + vars->player.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = (int)((vars->screen.width / 2) * (1 + transformX / transformY));

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(vars->screen.height / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + vars->screen.height / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + vars->screen.height / 2;
      if(drawEndY >= vars->screen.height) drawEndY = vars->screen.height - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int)(vars->screen.height / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= vars->screen.width) drawEndX = vars->screen.width - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * vars->sprite.width / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < vars->screen.width && transformY < vars->zbuffer[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y) * 256 - vars->screen.height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * vars->sprite.heigth) / spriteHeight) / 256;
          int color = ((int *)vars->sprite.addr)[vars->sprite.width * texY + texX]; //get current color from the texture
		  if (color != 0x000000)
          pixel_put(&img, stripe, y, color);
        }
      }
    }


	mlx_put_image_to_window(vars->mlx, vars->window, img.img, 0, 0);
	if (img.img)
		mlx_destroy_image(vars->mlx, img.img);
	
	return (1);
}

