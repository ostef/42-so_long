/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 04:38:01 by soumanso          #+#    #+#             */
/*   Updated: 2021/12/20 14:55:54 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool	game_init(t_game *game)
{
	game->mlx = mlx_init ();
	if (!game->mlx)
		return (FALSE);
	game->screen_width = ft_min (MAX_WIDTH, game->width);
	game->screen_height = ft_min (MAX_HEIGHT, game->height);
	game->mlx_win = mlx_new_window (game->mlx,
		game->screen_width * TILE_SIZE * GAME_SCALE,
		game->screen_height * TILE_SIZE * GAME_SCALE,
		"so_long");
	if (!game->mlx_win)
		return (FALSE);
	if (!img_init (game, &game->frame,
		game->screen_width * TILE_SIZE * GAME_SCALE,
		game->screen_height * TILE_SIZE * GAME_SCALE))
		return (FALSE);
	if (!img_load_png (game, &game->atlas, "data/atlas.png"))
		return (FALSE);
	game->running = TRUE;
	return (TRUE);
}

void	game_terminate(t_game *game, t_int error_code)
{
	ft_free (game->cells, ALLOC_HEAP);
	img_destroy (game, &game->frame);
	mlx_destroy_window (game->mlx, game->mlx_win);
	game->running = FALSE;
	exit (error_code);
}

t_bool	game_should_end(t_game *game)
{
	t_int	x;
	t_int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game_get_cell (game, x, y) == COLLECTIBLE)
				return (FALSE);
			x += 1;
		}
		y += 1;
	}
	return (game_get_cell (game, game->player_x, game->player_y) == EXIT);
}

static t_bool	move_block(t_game *game, t_int x, t_int y, t_int xdir, t_int ydir)
{
	t_cell	next;

	next = game_get_cell (game, x + xdir, y + ydir);
	if (next != AIR)
		return (FALSE);
	game_set_cell (game, x + xdir, y + ydir, BLOCK);
	game_set_cell (game, x, y, AIR);
	return (TRUE);
}

void	game_move(t_game *game, t_int xdir, t_int ydir)
{
	t_cell	next;
	t_int	next_x;
	t_int	next_y;

	next_x = game->player_x + xdir;
	next_y = game->player_y + ydir;
	next = game_get_cell (game, next_x, next_y);
	if (next == WALL)
		return ;
	if (next == COLLECTIBLE)
		game_set_cell (game, next_x, next_y, AIR);
	if (next == BLOCK && !move_block (game, next_x, next_y, xdir, ydir))
		return ;
	game->player_x = next_x;
	game->player_y = next_y;
	game->move_count += 1;
	game->cam_x = ft_clamp (game->player_x - game->screen_width / 2, 0, game->width - game->screen_width);
	game->cam_y = ft_clamp (game->player_y - game->screen_height / 2, 0, game->height - game->screen_height);
	ft_println ("Moves: %i.", game->move_count);
}
