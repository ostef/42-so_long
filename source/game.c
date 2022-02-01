/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 04:38:01 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/01 19:06:05 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool	game_init(t_game *game)
{
	game->mlx = mlx_init ();
	if (!game->mlx)
		return (FALSE);
	game->visible_tiles_x = ft_min (MAX_WIDTH, game->width);
	game->visible_tiles_y = ft_min (MAX_HEIGHT, game->height);
	game->mlx_win = mlx_new_window (game->mlx,
			game->visible_tiles_x * TILE_SIZE * GAME_SCALE,
			game->visible_tiles_y * TILE_SIZE * GAME_SCALE,
			"so_long");
	if (!game->mlx_win)
		return (FALSE);
	if (!img_init (game, &game->frame,
			game->visible_tiles_x * TILE_SIZE * GAME_SCALE,
			game->visible_tiles_y * TILE_SIZE * GAME_SCALE))
		return (FALSE);
	if (!img_load_xpm (game, &game->atlas, "data/atlas.xpm"))
		return (FALSE);
	game->player_tile = TILE_PLAYER_DOWN0;
	game->running = TRUE;
	return (TRUE);
}

void	game_terminate(t_game *game, t_int error_code)
{
	if (game->running)
	{
		ft_free (game->cells, ALLOC_HEAP);
		img_destroy (game, &game->frame);
		img_destroy (game, &game->atlas);
		game->running = FALSE;
		if (game->mlx && game->mlx_win)
			mlx_destroy_window (game->mlx, game->mlx_win);
		ft_memset (game, 0, sizeof (t_game));
	}
	if (ft_get_heap_allocations () != 0)
		ft_println ("Primitive leak checker: %i leaks from ft_alloc.",
			ft_get_heap_allocations ());
	exit (error_code);
}

t_bool	game_should_end(t_game *game)
{
	return (game_get_cell (game, game->player_x, game->player_y) == EXIT
		&& game->collectibles == 0);
}

void	game_move(t_game *game, t_dir dir)
{
	t_cell	next;
	t_int	next_x;
	t_int	next_y;
	t_int	xdir;
	t_int	ydir;

	get_xdir_ydir (dir, &xdir, &ydir);
	next_x = game->player_x + xdir;
	next_y = game->player_y + ydir;
	next = game_get_cell (game, next_x, next_y);
	if (next == WALL)
		return ;
	if (next == COLLECTIBLE)
		game_set_cell (game, next_x, next_y, AIR);
	game->player_x = next_x;
	game->player_y = next_y;
	game->player_tile = get_player_tile (xdir, ydir);
	game->move_count += 1;
	game->cam_x = ft_clamp (game->player_x - game->visible_tiles_x / 2, 0,
			game->width - game->visible_tiles_x);
	game->cam_y = ft_clamp (game->player_y - game->visible_tiles_y / 2, 0,
			game->height - game->visible_tiles_y);
}
