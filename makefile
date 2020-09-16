NAME=cub3d
#CFLAGS=-Wall -Werror -Wextra
SRCS=main.c utils.c map/map.c map/parse.c vector/point.c vector/vector.c render/render.c render/draw.c
OBJS=$(SRCS:.c=.o)
SANITIZE=-g -fsanitize=address
MATH=-lm
all: $(NAME)

$(NAME): $(OBJS)
	make -C ./minilibx
	gcc $(OBJS) $(SANITIZE) -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(MATH)

all: $(NAME)

clean:
	rm -f $(OBJS)
	#make clean -C ./minilibx

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
