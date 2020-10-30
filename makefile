NAME = cub3d
#CFLAGS = -Wall -Werror -Wextra
GNL = ./parser_cub/get_next_line/get_next_line.c
PARSER_SRCS	= ./parser_cub/parser_color.c ./parser_cub/parser_file.c ./parser_cub/parser_map.c ./parser_cub/parser_resolution.c ./parser_cub/parser_texture.c ./parser_cub/parser_utils.c ./parser_cub/parser_vars.c ./parser_cub/parser_sprites.c $(GNL)
SRCS = main.c vector/point.c vector/vector.c render/render.c render/draw.c $(PARSER_SRCS)
OBJS=$(SRCS:.c=.o)
CC=gcc
SANITIZE=-g -fsanitize=address
MATH=-lm
all: $(NAME)

$(NAME): $(OBJS)
	make -C ./minilibx
	make -C ./libft
	cp ./libft/libft.a .
	gcc $(OBJS) $(SANITIZE) -Lminilibx -lmlx -framework OpenGL -framework AppKit -L./ -lft -o $(NAME) $(MATH)

all: $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C ./minilibx

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
