NAME = cub3d

SRC = cub3d.c \
	parse.c \
	check1.c \
	check2.c \
	init_mlx.c \
	key.c 		\
	Get_Next_Line/get_next_line.c 	  \
    Get_Next_Line/get_next_line_utils.c \
	ft_printf/ft_format.c			\
	ft_printf/ft_printhex.c			\
	ft_printf/ft_printf.c			\
	ft_printf/ft_pointer.c		\
	ft_printf/ft_printunsigned.c		\
	ft_printf/ft_putchar.c			\
	ft_printf/ft_putnbr.c			\
	ft_printf/ft_putstr.c

CC = cc

CFLAGS = -g3 -Wall -Wextra -Werror -fsanitize=address -g3

LIBS = -I mlx -L mlx -l mlx -framework OpenGL -framework AppKit mlx/libmlx.a libft/libft.a

OUT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OUT)
	(cd libft && make)
	(cd mlx && make)
	$(CC) $(CFLAGS) $(OUT) $(LIBS) -o $(NAME)

clean:
	rm -f $(OUT)

fclean: clean
	rm -f $(NAME) && cd mlx && make clean
	cd libft && make fclean

re: fclean all