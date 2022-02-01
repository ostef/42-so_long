NAME = so_long
SRC_FILES = source/main.c source/game.c source/map.c source/rgba.c source/img.c source/draw.c source/utils.c source/load_map.c
OBJ_FILES = $(SRC_FILES:.c=.o)
INCLUDE_FILES = so_long.h
INCLUDE_DIRS = libft mlx .
LIB_DIRS = libft mlx
LIBS = ft mlx
CC = gcc
C_FLAGS = $(addprefix -I, $(INCLUDE_DIRS)) -Wall -Wextra -Werror

all: $(NAME)

$(OBJ_FILES): %.o: %.c $(INCLUDE_FILES)
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME): libft mlx $(OBJ_FILES)
	$(CC) $(addprefix -L, $(LIB_DIRS)) $(addprefix -l, $(LIBS)) -framework OpenGL -framework AppKit $(OBJ_FILES) -o $(NAME)

libft:
	make -C libft

mlx:
	make -C mlx
	cp mlx/libmlx.dylib .

fclean_libs:
	make -C libft fclean
	make -C mlx fclean

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f libmlx.dylib
	rm -f $(NAME)

re: fclean all

.PHONY: all libft mlx clean fclean
