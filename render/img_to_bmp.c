/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 10:49:34 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 11:06:57 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_bmp_file_header(unsigned char *bmpfileheader, int filesize)
{
	bmpfileheader[0] = 'B';
	bmpfileheader[1] = 'M';
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);
	bmpfileheader[10] = 54;
}

void	set_bmp_info_header(t_vars *vars, unsigned char *bmpinfoheader,
							t_img *img)
{
	bmpinfoheader[0] = 40;
	bmpinfoheader[4] = (unsigned char)(vars->window.width);
	bmpinfoheader[5] = (unsigned char)(vars->window.width >> 8);
	bmpinfoheader[6] = (unsigned char)(vars->window.width >> 16);
	bmpinfoheader[7] = (unsigned char)(vars->window.width >> 24);
	bmpinfoheader[8] = (unsigned char)(vars->window.height);
	bmpinfoheader[9] = (unsigned char)(vars->window.height >> 8);
	bmpinfoheader[10] = (unsigned char)(vars->window.height >> 16);
	bmpinfoheader[11] = (unsigned char)(vars->window.height >> 24);
	bmpinfoheader[12] = 1;
	bmpinfoheader[14] = img->bits_per_pixel;
}

void	write_bmp_img(t_vars *vars, int file, unsigned int *addr)
{
	int i;
	int j;

	i = vars->window.height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < vars->window.width)
		{
			write(file, &addr[i * vars->window.width + j], 4);
			j++;
		}
		i--;
	}
}

void	frame_to_bmp(t_vars *vars, t_img img)
{
	int				file;
	int				filesize;
	unsigned char	bmpfileheader[14];
	unsigned char	bmpinfoheader[40];
	unsigned int	*addr;

	ft_bzero(&bmpfileheader, 14);
	ft_bzero(&bmpinfoheader, 40);
	filesize = 54 + vars->window.width * vars->window.height
		* img.bits_per_pixel / 8;
	set_bmp_file_header(bmpfileheader, filesize);
	set_bmp_info_header(vars, bmpinfoheader, &img);
	file = open("./foto.bmp", O_WRONLY | O_CREAT, 0777);
	write(file, bmpfileheader, 14);
	write(file, bmpinfoheader, 40);
	addr = (unsigned int *)img.addr;
	write_bmp_img(vars, file, addr);
	close(file);
}
