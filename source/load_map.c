/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:24:01 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/01 15:50:51 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_bool	map_set_cell(t_game *game, t_int x, t_int y, t_cell cell)
{
	ft_assert (x >= 0 && x < game->width,
		"game_get_cell: x (%i) is out of bounds.", x);
	ft_assert (y >= 0 && y < game->height,
		"game_get_cell: y (%i) is out of bounds.", y);
	if (cell == 'P')
	{
		game->player_x = x;
		game->player_y = y;
		cell = AIR;
	}
	if (cell != AIR && cell != WALL && cell != COLLECTIBLE
		&& cell != EXIT && cell != BLOCK)
		return (FALSE);
	if (cell == EXIT)
		game->exits += 1;
	if (cell == COLLECTIBLE)
		game->collectibles += 1;
	game->cells[y * game->width + x] = cell;
	return (TRUE);
}

static t_bool	parse_map(t_game *game, t_cstr str)
{
	t_int	i;
	t_int	x;
	t_int	y;

	i = 0;
	x = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			x = 0;
			i += 1;
			y += 1;
			continue ;
		}
		if (str[i] == 'P' && game->player_x != -1 && game->player_y != -1)
			return (FALSE);
		if (!map_set_cell (game, x, y, str[i]))
			return (FALSE);
		x += 1;
		i += 1;
	}
	return (TRUE);
}

t_bool	game_load_map(t_game *game, t_cstr filename)
{
	t_str	str;

	str = ft_read_entire_file (filename, ALLOC_HEAP);
	if (!str)
		return (FALSE);
	ft_free (game->cells, ALLOC_HEAP);
	count_map_size (game, str);
	game->cells = (t_cell *)ft_zalloc (
			sizeof (t_cell) * game->width * game->height, ALLOC_HEAP);
	if (!game->cells)
		return (FALSE);
	game->player_x = -1;
	game->player_y = -1;
	if (!parse_map (game, str))
		return (FALSE);
	ft_free (str, ALLOC_HEAP);
	return (game->player_x != -1 && game->player_y != -1 && check_map (game));
}
