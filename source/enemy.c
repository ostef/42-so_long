/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:19:39 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/03 12:01:24 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	decide_next_move(t_enemy *enemy)
{
	t_int	rand;

	rand = ft_rand_rangei (0, 3);
	if (rand == 0)
	{
		enemy->xdir = 0;
		enemy->ydir = 1;
	}
	else if (rand == 1)
	{
		enemy->xdir = 0;
		enemy->ydir = -1;
	}
	else if (rand == 2)
	{
		enemy->xdir = 1;
		enemy->ydir = 0;
	}
	else if (rand == 3)
	{
		enemy->xdir = -1;
		enemy->ydir = 0;
	}
	enemy->steps = 0;
}

void	draw_enemies(t_game *game)
{
	t_int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		draw_tile (game, game->enemies[i].x * TILE_SIZE,
			game->enemies[i].y * TILE_SIZE, TILE_BLOCK);
		i += 1;
	}
}
