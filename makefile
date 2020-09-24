NAME=cub3d
#CFLAGS=-Wall -Werror -Wextra
SRCS=main.c vector/point.c vector/vector.c render/render.c render/draw.c file/file.c
GET_NEXT_LINE = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS=$(SRCS:.c=.o)
SANITIZE=-g -fsanitize=address
MATH=-lm
all: $(NAME)

$(NAME): $(OBJS)
	make -C ./minilibx
	gcc $(OBJS) $(GET_NEXT_LINE) $(SANITIZE) -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME) $(MATH)

all: $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C ./minilibx

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
