/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 05:15:57 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/02 15:27:50 by soumanso         ###   ########lyon.fr   */
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
	if (game_get_cell (game, x, y) == COLLECTIBLE)
		game->collectibles -= 1;
	game->cells[y * game->width + x] = cell;
}

t_bool	count_map_size(t_game *game, t_str str)
{
	t_int	i;
	t_int	width;

	game->width = 0;
	game->height = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == 0)
		{
			if (game->height == 0)
				width = game->width;
			if (game->width != width)
				return (FALSE);
			game->height += 1;
			if (str[i] == 0)
				break ;
			else
				game->width = -1;
		}
		if (str[i] != '\r')
			game->width += 1;
		i += 1;
	}
	return (game->width > 0 && game->height > 0);
}

t_err	check_map(t_game *game)
{
	t_int	x;
	t_int	y;
	t_cell	cell;

	if (game->exits == 0)
		return (ERR_MAP_NO_EXIT);
	if (game->collectibles == 0)
		return (ERR_MAP_NO_COLLECTIBLE);
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			cell = game_get_cell (game, x, y);
			if ((x == 0 || x == game->width - 1
					|| y == 0 || y == game->height - 1) && cell != WALL)
				return (ERR_MAP_NOT_CLOSED);
			x += 1;
		}
		y += 1;
	}
	return (OK);
}
