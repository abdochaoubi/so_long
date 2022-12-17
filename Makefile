cc = gcc
SRC = main.c ./getsky/lol.c ./getsky/get_next_line.c ./getsky/get_next_line_utils.c ft_itoa.c ft_split.c
NAME = so_long
OBJ = $(SRC:.c=.o)

Flags = -Wall -Wextra -Werror


$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# all: $(NAME)

fclean :
	rm -rf $(OBJ) dsds