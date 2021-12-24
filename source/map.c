/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 05:15:57 by soumanso          #+#    #+#             */
/*   Updated: 2021/12/20 16:17:17 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_cell	game_get_cell(t_game *game, t_int x, t_int y)
{
	ft_assert (x >= 0 && x < game->width,
		"game_get_cell: x (%i) is out of bounds.", x);
	ft_assert (y >= 0 && y < game->height,
		"game_get_cell: y (%i) is out of bounds.", y);
	return (game->cells[y * game->width + x]);
}

void	game_set_cell(t_game *game, t_int x, t_int y, t_cell cell)
{
	ft_assert (x >= 0 && x < game->width,
		"game_get_cell: x (%i) is out of bounds.", x);
	ft_assert (y >= 0 && y < game->height,
		"game_get_cell: y (%i) is out of bounds.", y);
	game->cells[y * game->width + x] = cell;
}

static t_bool	count_map_size(t_game *game, t_str str)
{
	t_int	i;

	game->width = 0;
	game->height = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			game->width = -1;
			game->height += 1;
		}
		game->width += 1;
		i += 1;
	}
	return (TRUE);
}

static t_bool	check_map(t_game *game)
{
	t_int	x;
	t_int	y;
	t_cell	cell;
	t_bool	has_collectible;
	t_bool	has_exit;

	has_collectible = FALSE;
	has_exit = FALSE;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			cell = game_get_cell (game, x, y);
			if ((x == 0 || x == game->width - 1) && cell != WALL)
				return (FALSE);
			if ((y == 0 || y == game->height - 1) && cell != WALL)
				return (FALSE);
			if (cell == COLLECTIBLE)
				has_collectible = TRUE;
			if (cell == EXIT)
				has_exit = TRUE;
			x += 1;
		}
		y += 1;
	}
	return (has_collectible && has_exit);
}

t_bool	game_load_map(t_game *game, t_cstr filename)
{
	t_str	str;
	t_int	x;
	t_int	y;
	t_int	i;
	t_bool	found_player;

	str = ft_read_entire_file (filename, ALLOC_TEMP);
	if (!str)
		return (FALSE);
	ft_free (game->cells, ALLOC_HEAP);
	if (!count_map_size (game, str))
		return (FALSE);
	game->cells = (t_cell *)ft_alloc (
			sizeof (t_cell) * game->width * game->height, ALLOC_HEAP);
	if (!game->cells)
		return (FALSE);
	i = 0;
	x = 0;
	y = 0;
	found_player = FALSE;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			x = -1;
			y += 1;
		}
		else if (str[i] == 'P')
		{
			if (found_player)
				return (FALSE);
			game->player_x = x;
			game->player_y = y;
			game_set_cell (game, x, y, AIR);
			found_player = TRUE;
		}
		else
		{
			game_set_cell (game, x, y, str[i]);
		}
		x += 1;
		i += 1;
	}
	return (found_player && check_map (game));
}
