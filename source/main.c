/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:35:28 by soumanso          #+#    #+#             */
/*   Updated: 2021/12/20 16:17:44 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fatal_error(t_game *game, t_cstr fmt, ...)
{
	va_list	va;

	ft_fprintln (STDERR, "Error");
	va_start (va, fmt);
	ft_vfprintln (STDERR, fmt, va);
	va_end (va);
	game_terminate (game, 1);
}

static void	draw_map(t_game *game)
{
	t_int	x;
	t_int	y;

	y = 0;
	while (y < game->screen_height)
	{
		x = 0;
		while (x < game->screen_width)
		{
			t_cell cell = game_get_cell (game, x + game->cam_x, y + game->cam_y);
			if (cell == WALL)
				draw_tile (game, x * TILE_SIZE, y * TILE_SIZE, TILE_WALL);
			else if (cell == COLLECTIBLE)
				draw_tile (game, x * TILE_SIZE, y * TILE_SIZE, TILE_COLLECTIBLE);
			else if (cell == EXIT)
				draw_tile (game, x * TILE_SIZE, y * TILE_SIZE, TILE_EXIT);
			else if (cell == BLOCK)
				draw_tile (game, x * TILE_SIZE, y * TILE_SIZE, TILE_BLOCK);
			if (x + game->cam_x == game->player_x
				&& y + game->cam_y == game->player_y)
				draw_tile (game, x * TILE_SIZE, y * TILE_SIZE, TILE_PLAYER_DOWN0);
			x += 1;
		}
		y += 1;
	}
}

static t_int	main_loop(t_game *game)
{
	ft_reset_temp_storage ();
	if (!game->running)
		return (0);
	draw_clear (game, rgb (0, 0, 0));
	draw_map (game);
	mlx_put_image_to_window (game->mlx, game->mlx_win,
		game->frame.mlx_img, 0, 0);
	mlx_do_sync (game->mlx);
	return (0);
}

static t_int	key_hook(t_int key_code, t_game *game)
{
	if (key_code == KEY_W)
		game_move (game, 0, -1);
	else if (key_code == KEY_A)
		game_move (game, -1, 0);
	else if (key_code == KEY_S)
		game_move (game, 0, 1);
	else if (key_code == KEY_D)
		game_move (game, 1, 0);
	if (game_should_end (game) || key_code == KEY_ESCAPE)
		game_terminate (game, 0);
	return (0);
}

t_int	main(t_int argc, t_str *args)
{
	t_game	game;

	if (argc != 2)
	{
		ft_fprintln (STDERR, "Usage: so_long map_filename");
		return (1);
	}
	ft_memset (&game, 0, sizeof (t_game));
	if (!game_load_map (&game, args[1]))
		fatal_error (&game, "Could not load map '%s'.", args[1]);
	if (!game_init (&game))
		fatal_error (&game, "Could not initialize game.");
	mlx_hook (game.mlx_win, 2, 1L << 0, key_hook, &game);
	mlx_loop_hook (game.mlx, main_loop, &game);
	mlx_loop (game.mlx);
	return (0);
}
