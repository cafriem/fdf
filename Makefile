NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Ofast

SRCS =	fdf.c						\
		fdf_points_draw.c			\
		fdf_isometric.c				\
		fdf_reading_lines.c			\
		fdf_keypress.c				\
		fdf_legends.c				\
		fdf_free.c					\
		get_next_line_bonus.c		\
		get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)

CC = gcc

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

LIBS =	Libft/libft.a

$(NAME): $(OBJS)
	make -C Libft
	make -C MLX
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

all: $(NAME)

clean:
	make -C MLX clean
	rm -f $(OBJS)
	make -C Libft clean

fclean: clean
	rm -f $(NAME)
	rm -f *.dylib
	make -C Libft fclean

re: fclean all