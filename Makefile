NAME = so_long
SRC_FILES = source/main.c source/game.c source/map.c source/load_map.c source/enemy.c\
	source/rgba.c source/img.c source/draw.c source/font.c\
	source/utils.c  source/error.c
OBJ_FILES = $(SRC_FILES:.c=.o)
INCLUDE_FILES = so_long.h
INCLUDE_DIRS = libft mlx .
DEPENDENCIES = libft/libft.a mlx/libmlx.dylib
LIB_DIRS = libft mlx
LIBS = ft mlx
CC = gcc
C_FLAGS = $(addprefix -I, $(INCLUDE_DIRS)) -Wall -Wextra -Werror

all: | libft mlx $(NAME)

$(OBJ_FILES): %.o: %.c $(INCLUDE_FILES) $(DEPENDENCIES) Makefile
	$(CC) $(C_FLAGS) -c $< -o $@

$(NAME): $(OBJ_FILES)
	$(CC) $(addprefix -L, $(LIB_DIRS)) $(addprefix -l, $(LIBS)) -framework OpenGL -framework AppKit $(OBJ_FILES) -o $(NAME)
	cp mlx/libmlx.dylib .

libft:
	@make -C libft

mlx:
	@make -C mlx

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f libmlx.dylib
	rm -f $(NAME)

fclean_libs:
	make -C libft fclean
	make -C mlx fclean

re: fclean all

.PHONY: all libft mlx clean fclean
