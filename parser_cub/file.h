/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apavel <apavel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:40:28 by apavel            #+#    #+#             */
/*   Updated: 2020/11/05 10:41:26 by apavel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../entities/sprite.h"

typedef struct	s_parser
{
	int			w_width;
	int			w_height;
	char		*texture_north;
	char		*texture_south;
	char		*texture_west;
	char		*texture_east;
	char		*sprite_texture;
	int			f_c[3];
	int			c_c[3];
	int			map_width;
	int			map_height;
	char		**map;
	int			player_dir;
	int			player_x;
	int			player_y;
	int			sprite_number;
	int			empty_line;
	int			map_started;
	t_sprite	*sprite_order;
}				t_parser;

int				read_file(t_parser *vars, const char *file_name);
int				empty_end_of_line(char *str);
void			flood_fill(t_parser *vars, int x, int y, int prev_color);
int				parse_resolution_line(t_parser *vars, char *str);
int				parse_texture_line(t_parser *vars, int type, char *str);
int				parse_color_line(t_parser *vars, int type, char *str);
void			initialize_vars(t_parser *vars);
int				check_variables(t_parser *vars);
int				count_map_size(t_parser *vars, char *str);
int				check_player_pos(t_parser *vars, int y, char *str);
int				parse_map(t_parser *vars, int fd);
int				check_file_name(const char *str);
void			convert_map(t_parser *vars);
void			detect_sprites(t_parser *vars);

#endif
