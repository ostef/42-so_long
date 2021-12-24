/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:48:15 by soumanso          #+#    #+#             */
/*   Updated: 2021/12/15 18:25:01 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_rgba	rgba(t_u8 r, t_u8 g, t_u8 b, t_u8 a)
{
	t_rgba	res;

	res.r = r;
	res.g = g;
	res.b = b;
	res.a = a;
	return (res);
}

t_rgba	rgb(t_u8 r, t_u8 g, t_u8 b)
{
	return (rgba (r, g, b, 255));
}

t_trgb	rgba_to_trgb(t_rgba rgba)
{
	return ((255 - rgba.a) << 24 | rgba.r << 16 | rgba.g << 8 | rgba.b);
}

t_rgba	trgb_to_rgba(t_trgb trgb)
{
	t_rgba	res;

	res.r = (trgb >> 16) & 0xff;
	res.g = (trgb >> 8) & 0xff;
	res.b = trgb & 0xff;
	res.a = 255 - ((trgb >> 24) & 0xff);
	return (res);
}

t_rgba	rgba_blend(t_rgba a, t_rgba b)
{
	t_f32	fa;
	t_f32	fr;
	t_f32	fg;
	t_f32	fb;

	fa = b.a / 255.0f;
	fr = b.r / 255.0f * fa + a.r / 255.0f * (1.0f - fa);
	fg = b.g / 255.0f * fa + a.g / 255.0f * (1.0f - fa);
	fb = b.b / 255.0f * fa + a.b / 255.0f * (1.0f - fa);
	return (rgb (fr * 255, fg * 255, fb * 255));
}
