/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:35:28 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/01 17:44:47 by soumanso         ###   ########lyon.fr   */
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

static t_int	main_loop(t_game *game)
{
	t_int	moves_strlen;
	t_str	moves_str;

	ft_reset_temp_storage ();
	if (!game->running)
		return (0);
	draw_clear (game, rgb (0, 0, 0));
	draw_map (game);
	mlx_put_image_to_window (game->mlx, game->mlx_win,
		game->frame.mlx_img, 0, 0);
	moves_strlen = ft_sprint (NULL, "Moves: %i", game->move_count);
	moves_str = (t_str)ft_alloc (moves_strlen + 1, ALLOC_TEMP);
	ft_sprint (moves_str, "Moves: %i", game->move_count);
	mlx_string_put (game->mlx, game->mlx_win, 10, 10,
		rgba_to_trgb (rgba (255, 255, 255, 255)), moves_str);
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

static t_int	destroy_hook(t_game *game)
{
	game->mlx_win = NULL;
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
	mlx_hook (game.mlx_win, 17, 0, destroy_hook, &game);
	mlx_loop_hook (game.mlx, main_loop, &game);
	mlx_loop (game.mlx);
	return (0);
}
