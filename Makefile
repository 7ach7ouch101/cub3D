NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRCS = cub3d.c get_next_line.c tools.c tools1.c tools2.c parse_map.c parse_map1.c parse_param.c parse_param1.c parse_param2.c movement.c position_player.c raycasting.c render.c get_map.c ft_error.c raycasting_norm.c render_norm.c

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