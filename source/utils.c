/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:58:12 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/01 16:33:33 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_xdir_ydir(t_dir dir, t_int *x, t_int *y)
{
	*x = 0;
	*y = 0;
	if (dir == DOWN)
		*y = 1;
	else if (dir == UP)
		*y = -1;
	else if (dir == RIGHT)
		*x = 1;
	else if (dir == LEFT)
		*x = -1;
}

t_int	cell_to_tile(t_cell cell)
{
	if (cell == WALL)
		return (TILE_WALL);
	if (cell == COLLECTIBLE)
		return (TILE_COLLECTIBLE);
	if (cell == EXIT)
		return (TILE_EXIT);
	return (-1);
}

t_cell	tile_to_cell(t_int tile)
{
	if (tile == TILE_WALL)
		return (WALL);
	if (tile == TILE_COLLECTIBLE)
		return (COLLECTIBLE);
	if (tile == TILE_EXIT)
		return (EXIT);
	return (-1);
}

t_int	get_player_tile(t_int xdir, t_int ydir)
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
		return (-1);
	return (TILE_PLAYER_DOWN0 + tile_offset * 2);
}
