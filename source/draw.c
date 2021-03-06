/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 04:05:54 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/03 12:17:23 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_clear(t_game *game, t_rgba color)
{
	t_int	x;
	t_int	y;

	y = 0;
	while (y < game->frame.height)
	{
		x = 0;
		while (x < game->frame.width)
		{
			img_set_px (&game->frame, x, y, color);
			x += 1;
		}
		y += 1;
	}
}

void	draw_px(t_game *game, t_int x, t_int y, t_rgba color)
{
	t_int	xx;
	t_int	yy;

	color = rgba_blend (
			img_get_px (&game->frame, x * GAME_SCALE, y * GAME_SCALE), color);
	yy = y * GAME_SCALE;
	while (yy < y * GAME_SCALE + GAME_SCALE)
	{
		xx = x * GAME_SCALE;
		while (xx < x * GAME_SCALE + GAME_SCALE)
		{
			img_set_px (&game->frame, xx, yy, color);
			xx += 1;
		}
		yy += 1;
	}
}

void	draw_img(t_game *game, t_int x, t_int y, t_img *img)
{
	t_int	xx;
	t_int	yy;

	yy = 0;
	while (yy < img->height)
	{
		xx = 0;
		while (xx < img->width)
		{
			draw_px (game, x + xx, y + yy, img_get_px (img, xx, yy));
			xx += 1;
		}
		yy += 1;
	}
}

void	draw_tile(t_game *game, t_int x, t_int y, t_tile tile)
{
	t_int	tile_x;
	t_int	tile_y;
	t_int	xx;
	t_int	yy;

	tile_x = tile % (game->atlas.width / TILE_SIZE);
	tile_y = tile / (game->atlas.width / TILE_SIZE);
	yy = 0;
	while (yy < TILE_SIZE)
	{
		xx = 0;
		while (xx < TILE_SIZE)
		{
			draw_px (game, x + xx, y + yy,
				img_get_px (&game->atlas,
					tile_x * TILE_SIZE + xx,
					tile_y * TILE_SIZE + yy));
			xx += 1;
		}
		yy += 1;
	}
}

void	draw_map(t_game *game)
{
	t_int	x;
	t_int	y;
	t_cell	cell;
	t_tile	tile;

	y = 0;
	while (y < game->visible_tiles_y)
	{
		x = 0;
		while (x < game->visible_tiles_x)
		{
			cell = game_get_cell (game, x + game->cam_x, y + game->cam_y);
			tile = cell_to_tile (cell);
			if (tile != TILE_INVALID)
				draw_tile (game, x * TILE_SIZE, y * TILE_SIZE, tile);
			if (x + game->cam_x == game->player_x
				&& y + game->cam_y == game->player_y)
				draw_tile (game, x * TILE_SIZE, y * TILE_SIZE,
					game->player_tile + (game->move_count % 2));
			x += 1;
		}
		y += 1;
	}
}
