/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:09:26 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/02 15:39:45 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_px_unscaled(t_game *game, t_int x, t_int y, t_rgba color)
{
	color = rgba_blend (
			img_get_px (&game->frame, x, y), color);
	img_set_px (&game->frame, x, y, color);
}

void	draw_char(t_game *game, t_int x, t_int y, char c)
{
	t_int	xx;
	t_int	yy;

	c = ft_to_upper (c);
	if (c < FONT_FIRST_CHAR || c > FONT_LAST_CHAR)
		return ;
	c -= FONT_FIRST_CHAR;
	yy = 0;
	while (yy < FONT_GLYPH_WIDTH)
	{
		xx = 0;
		while (xx < FONT_GLYPH_HEIGHT)
		{
			draw_px_unscaled (game, x + xx, y + yy,
				img_get_px (&game->font, c * FONT_GLYPH_WIDTH + xx, yy));
			xx += 1;
		}
		yy += 1;
	}
}

void	draw_text(t_game *game, t_int x, t_int y, t_cstr str)
{
	t_int	i;
	t_int	xx;
	t_int	yy;

	xx = x;
	yy = y;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			xx = x;
			yy += FONT_GLYPH_HEIGHT;
		}
		else
		{
			draw_char (game, xx, yy, str[i]);
			xx += FONT_GLYPH_WIDTH;
		}
		i += 1;
	}
}
