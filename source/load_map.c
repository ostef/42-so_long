/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:24:01 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/03 12:02:02 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_bool	map_set_cell(t_game *game, t_int x, t_int y, t_cell cell)
{
	ft_assert (x >= 0 && x < game->width,
		"map_set_cell: x (%i) is out of bounds %i.", x, game->width);
	ft_assert (y >= 0 && y < game->height,
		"map_set_cell: y (%i) is out of bounds %i.", y, game->height);
	if (cell == 'P')
	{
		game->player_x = x;
		game->player_y = y;
		cell = CELL_AIR;
	}
	if (cell == '#')
	{
		game->enemies[game->enemy_count].x = x;
		game->enemies[game->enemy_count].y = y;
		decide_next_move (&game->enemies[game->enemy_count]);
		game->enemy_count += 1;
		cell = CELL_AIR;
	}
	if (cell != CELL_AIR && cell != CELL_WALL && cell != CELL_COLLECTIBLE
		&& cell != CELL_EXIT)
		return (FALSE);
	if (cell == CELL_EXIT)
		game->exits += 1;
	if (cell == CELL_COLLECTIBLE)
		game->collectibles += 1;
	game->cells[y * game->width + x] = cell;
	return (TRUE);
}

static t_err	parse_map(t_game *game, t_cstr str)
{
	t_int	i;
	t_int	x;
	t_int	y;

	i = 0;
	x = 0;
	y = 0;
	game->enemy_count = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			x = 0;
			y += 1;
		}
		else if (str[i] != '\r')
		{
			if (str[i] == 'P' && game->player_x != -1 && game->player_y != -1)
				return (ERR_MAP_MULTIPLE_PLAYERS);
			if (!map_set_cell (game, x, y, str[i]))
				return (ERR_MAP_CELL);
			x += 1;
		}
		i += 1;
	}
	return (OK);
}

t_err	game_load_map(t_game *game, t_cstr filename)
{
	t_str	str;
	t_err	err;

	str = ft_read_entire_file (filename, ALLOC_TEMP);
	if (!str)
		return (ERR_FILE);
	if (!count_map_size (game, str))
		return (ERR_MAP_NOT_RECT);
	count_enemies (game, str);
	game->cells = (t_cell *)ft_zalloc (
			sizeof (t_cell) * game->width * game->height, ALLOC_HEAP);
	if (!game->cells)
		return (ERR_MEM);
	game->enemies = (t_enemy *)ft_zalloc (
			sizeof (t_enemy) * game->enemy_count, ALLOC_HEAP);
	if (game->enemy_count > 0 && !game->enemies)
		return (ERR_MEM);
	game->player_x = -1;
	game->player_y = -1;
	err = parse_map (game, str);
	if (err != OK)
		return (err);
	if (game->player_x == -1 || game->player_y == -1)
		return (ERR_MAP_NO_PLAYER);
	return (check_map (game));
}
