/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 05:15:57 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/01 16:35:45 by soumanso         ###   ########lyon.fr   */
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

void	count_map_size(t_game *game, t_str str)
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
}

t_bool	check_map(t_game *game)
{
	t_int	x;
	t_int	y;
	t_cell	cell;

	if (game->exits == 0 || game->collectibles == 0)
		return (FALSE);
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			cell = game_get_cell (game, x, y);
			if ((x == 0 || x == game->width - 1
					|| y == 0 || y == game->height - 1) && cell != WALL)
				return (FALSE);
			x += 1;
		}
		y += 1;
	}
	return (TRUE);
}
