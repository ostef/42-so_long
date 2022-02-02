/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:33:17 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/02 15:35:15 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "mlx.h"

# define TILE_SIZE 16
# ifndef GAME_SCALE
#  define GAME_SCALE 2
# endif
# ifndef MAX_WIDTH
#  define MAX_WIDTH 30
# endif
# ifndef MAX_HEIGHT
#  define MAX_HEIGHT 30
# endif

# define FONT_IMAGE_FILENAME "data/font.xpm"
# define ATLAS_IMAGE_FILENAME "data/atlas.xpm"

# define FONT_FIRST_CHAR ' '
# define FONT_LAST_CHAR 'Z'
# define FONT_GLYPH_WIDTH 16
# define FONT_GLYPH_HEIGHT 16

# define TILE_PLAYER_DOWN0 0
# define TILE_PLAYER_DOWN1 1
# define TILE_PLAYER_UP0 2
# define TILE_PLAYER_UP1 3
# define TILE_PLAYER_RIGHT0 4
# define TILE_PLAYER_RIGHT1 5
# define TILE_PLAYER_LEFT0 6
# define TILE_PLAYER_LEFT1 7
# define TILE_PLAYER_PUSHD0 8
# define TILE_PLAYER_PUSHD1 9
# define TILE_PLAYER_PUSHU0 10
# define TILE_PLAYER_PUSHU1 11
# define TILE_PLAYER_PUSHR0 12
# define TILE_PLAYER_PUSHR1 13
# define TILE_PLAYER_PUSHL0 14
# define TILE_PLAYER_PUSHL1 15
# define TILE_PLAYER_FALL0 16
# define TILE_PLAYER_FALL1 17
# define TILE_PLAYER_FALL2 18
# define TILE_AIR 19
# define TILE_COLLECTIBLE 20
# define TILE_WALL 22
# define TILE_EXIT 23

# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_SPACE 49
# define KEY_CTRL 256
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESCAPE 53

typedef t_u32	t_trgb;

typedef union u_rgba
{
	t_u32	value;
	struct
	{
		t_u8	r;
		t_u8	g;
		t_u8	b;
		t_u8	a;
	};
}	t_rgba;

t_rgba	rgba(t_u8 r, t_u8 g, t_u8 b, t_u8 a);
t_rgba	rgb(t_u8 r, t_u8 g, t_u8 b);
t_trgb	rgba_to_trgb(t_rgba rgba);
t_rgba	trgb_to_rgba(t_trgb trgb);
t_rgba	rgba_blend(t_rgba a, t_rgba b);

typedef struct s_img
{
	void	*mlx_img;
	void	*data;
	t_int	width;
	t_int	height;
	t_int	bits_per_px;
	t_int	line_len;
	t_int	endianness;
}	t_img;

typedef enum e_cell
{
	AIR = '0',
	WALL = '1',
	COLLECTIBLE = 'C',
	EXIT = 'E'
}	t_cell;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	t_bool	running;
	t_img	frame;
	t_img	atlas;
	t_img	font;
	t_cell	*cells;
	t_int	collectibles;
	t_int	exits;
	t_int	width;
	t_int	height;
	t_int	player_x;
	t_int	player_y;
	t_int	player_tile;
	t_int	move_count;
	t_int	visible_tiles_x;
	t_int	visible_tiles_y;
	t_int	cam_x;
	t_int	cam_y;
}	t_game;

typedef enum e_err
{
	OK = 0,
	ERR_FILE,
	ERR_MEM,
	ERR_MLX,
	ERR_IMG_ATLAS,
	ERR_IMG_FONT,
	ERR_MAP_CELL,
	ERR_MAP_NOT_CLOSED,
	ERR_MAP_NOT_RECT,
	ERR_MAP_NO_PLAYER,
	ERR_MAP_MULTIPLE_PLAYERS,
	ERR_MAP_NO_EXIT,
	ERR_MAP_NO_COLLECTIBLE,
	ERR_COUNT
}	t_err;

void	print_err(t_err err);

t_err	game_init(t_game *game);
void	game_terminate(t_game *game, t_err err);
t_err	game_load_map(t_game *game, t_cstr filename);
t_cell	game_get_cell(t_game *game, t_int x, t_int y);
void	game_set_cell(t_game *game, t_int x, t_int y, t_cell cell);
void	game_move(t_game *game, t_int xdir, t_int ydir);
t_bool	game_should_end(t_game *game);

t_bool	count_map_size(t_game *game, t_str str);
t_err	check_map(t_game *game);

t_bool	img_init(t_game *game, t_img *img, t_int width, t_int height);
void	img_destroy(t_game *game, t_img *img);
t_bool	img_load_xpm(t_game *game, t_img *img, t_cstr filename);
t_rgba	img_get_px(t_img *img, t_int x, t_int y);
void	img_set_px(t_img *img, t_int x, t_int y, t_rgba color);

void	draw_clear(t_game *game, t_rgba color);
void	draw_px(t_game *game, t_int x, t_int y, t_rgba color);
void	draw_img(t_game *game, t_int x, t_int y, t_img *img);
void	draw_tile(t_game *game, t_int x, t_int y, t_int tile);
void	draw_map(t_game *game);
void	draw_char(t_game *game, t_int x, t_int y, char c);
void	draw_text(t_game *game, t_int x, t_int y, t_cstr str);

t_int	cell_to_tile(t_cell cell);
t_cell	tile_to_cell(t_int tile);
t_int	get_player_tile(t_int xdir, t_int ydir);

#endif
