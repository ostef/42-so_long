/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:58:12 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/03 11:21:59 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_tile	cell_to_tile(t_cell cell)
{
	if (cell == CELL_WALL)
		return (TILE_WALL);
	if (cell == CELL_COLLECTIBLE)
		return (TILE_COLLECTIBLE);
	if (cell == CELL_EXIT)
		return (TILE_EXIT);
	return (TILE_INVALID);
}

t_cell	tile_to_cell(t_tile tile)
{
	if (tile == TILE_WALL)
		return (CELL_WALL);
	if (tile == TILE_COLLECTIBLE)
		return (CELL_COLLECTIBLE);
	if (tile == TILE_EXIT)
		return (CELL_EXIT);
	return (CELL_INVALID);
}

t_tile	get_player_tile(t_int xdir, t_int ydir)
{
	t_int	tile_offset;

	tile_offset = 0;
	if (xdir < 0)
		tile_offset = 3;
	else if (xdir > 0)
		tile_offset = 2;
	else if (ydir < 0)
		tile_offset = 1;
	else if (ydir > 0)
		tile_offset = 0;
	else
		return (TILE_INVALID);
	return (TILE_PLAYER_DOWN0 + tile_offset * 2);
}
