#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "cub3d.h"
#include "vector/point.h"
#include "render/render.h"
#include "get_next_line/get_next_line.h"
#include "file/file.h"

#define map_width 10
#define map_height 10

double player_x = 2;
double player_y = 2;

double player_dir = 0;
float player_speed = 0.2;
float player_rot = 3;
double fov = 60;

void close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->window);
	exit(0);
}

int	key_handler(int keycode, t_vars *vars)
{
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

	printf("keycode pressed: %d\n", keycode);
	if (keycode == 53)
		close_window(vars);
		
	if (keycode == 123)
	{
		double old_dir_x = vars->player.dir_x;
		vars->player.dir_x = vars->player.dir_x * cos(vars->player.rot_speed) - vars->player.dir_y * sin(vars->player.rot_speed);
		vars->player.dir_y = old_dir_x * sin(vars->player.rot_speed) + vars->player.dir_y * cos(vars->player.rot_speed);
		double oldPlaneX = vars->player.plane_x;
		vars->player.plane_x = vars->player.plane_x * cos(vars->player.rot_speed) - vars->player.plane_y * sin(vars->player.rot_speed);
		vars->player.plane_y = oldPlaneX * sin(vars->player.rot_speed) + vars->player.plane_y * cos(vars->player.rot_speed);
	}
	if (keycode == 124)
	{
		double old_dir_x = vars->player.dir_x;
		vars->player.dir_x = vars->player.dir_x * cos(-(vars->player.rot_speed)) - vars->player.dir_y * sin(-(vars->player.rot_speed));
		vars->player.dir_y = old_dir_x * sin(-(vars->player.rot_speed)) + vars->player.dir_y * cos(-(vars->player.rot_speed));
		double oldPlaneX = vars->player.plane_x;
		vars->player.plane_x = vars->player.plane_x * cos(-(vars->player.rot_speed)) - vars->player.plane_y * sin(-(vars->player.rot_speed));
		vars->player.plane_y = oldPlaneX * sin(-(vars->player.rot_speed)) + vars->player.plane_y * cos(-(vars->player.rot_speed));
	}

	//W
	if (keycode == 13)
	{
		if(map[(int)(vars->player.pos_x + vars->player.dir_x * vars->player.speed)][(int)vars->player.pos_y] == 0) vars->player.pos_x += vars->player.dir_x * vars->player.speed;
      	if(map[(int)vars->player.pos_x][(int)(vars->player.pos_y + vars->player.dir_y * vars->player.speed)] == 0) vars->player.pos_y += vars->player.dir_y * vars->player.speed;
	}
	//S
	if (keycode == 1)
	{
		if(map[(int)(vars->player.pos_x - vars->player.dir_x * vars->player.speed)][(int)vars->player.pos_y] == 0) vars->player.pos_x -= vars->player.dir_x * vars->player.speed;
      	if(map[(int)vars->player.pos_x][(int)(vars->player.pos_y - vars->player.dir_y * vars->player.speed)] == 0) vars->player.pos_y -= vars->player.dir_y * vars->player.speed;
	}
	//A
	if (keycode == 0)
	{
		
	}
	//D
	if (keycode == 2)
	{
		
	}
	return (1);
}

int	main(void)
{
	t_vars *vars;

	vars = malloc(sizeof(t_vars));
	
	vars->screen.width = 640;
	vars->screen.height = 480;
	
	vars->player.pos_x = 3;
	vars->player.pos_y = 3;
	vars->player.dir_x = -1;
	vars->player.dir_y = 0;
	vars->player.plane_x = 0;
	vars->player.plane_y = 0.66;
	vars->player.speed = 0.5;
	vars->player.rot_speed = 0.2;
	
	vars->zbuffer = malloc(sizeof(double) * vars->screen.width);

	vars->sprite_number = 2;
	vars->sprite_order = malloc(sizeof(t_sprite) * vars->sprite_number);

	vars->sprite_order[0].x = 7.5;
	vars->sprite_order[0].y = 2.5;

	vars->sprite_order[1].x = 2.5;
	vars->sprite_order[1].y = 2.5;

	int file_ok = check_file(&vars, "map.cub");

	/*
	vars->mlx = mlx_init();
	vars->window = mlx_new_window(vars->mlx, vars->screen.width, vars->screen.height, "cub3d");

	//load textures
	
	vars->texture_north.img = mlx_xpm_file_to_image(vars->mlx, "./textures/redbrick.xpm", &vars->texture_north.width, &vars->texture_north.heigth);
	vars->texture_north.addr = mlx_get_data_addr(vars->texture_north.img, &vars->texture_north.bits_per_pixel, &vars->texture_north.line_length, &vars->texture_north.endian);

	vars->sprite.img = mlx_xpm_file_to_image(vars->mlx, "./textures/barrel.xpm", &vars->sprite.width, &vars->sprite.heigth);
	vars->sprite.addr = mlx_get_data_addr(vars->sprite.img, &vars->sprite.bits_per_pixel, &vars->sprite.line_length, &vars->sprite.endian);
	
	render(vars);
	mlx_loop_hook(vars->mlx, render, vars);
	mlx_key_hook(vars->window, key_handler, vars);
	mlx_loop(vars->mlx);
	*/

	free(vars);
	return (0);
}
