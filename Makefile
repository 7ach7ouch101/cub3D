NAME = cub3D
CC = gcc
#CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRCS = cub3d.c get_next_line.c tools.c tools1.c
OBJ = $(SRCS:.c=.o)
MLX_API = -lmlx -framework OpenGL -framework AppKit

$(NAME): $(OBJ) cub3d.h
	$(CC) $(CFLAGS) $(MLX_API) $(OBJ) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all