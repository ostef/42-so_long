/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 03:41:16 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/01 13:14:32 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool	img_init(t_game *game, t_img *img, t_int width, t_int height)
{
	img->mlx_img = mlx_new_image (game->mlx, width, height);
	if (!img->mlx_img)
		return (FALSE);
	img->data = (void *)mlx_get_data_addr (img->mlx_img, &img->bits_per_px,
			&img->line_len, &img->endianness);
	if (!img->data)
		return (FALSE);
	img->width = width;
	img->height = height;
	return (TRUE);
}

void	img_destroy(t_game *game, t_img *img)
{
	if (game->mlx && img->mlx_img)
		mlx_destroy_image (game->mlx, img->mlx_img);
	ft_memset (img, 0, sizeof (t_img));
}

t_bool	img_load_png(t_game *game, t_img *img, t_cstr filename)
{
	img->mlx_img = mlx_png_file_to_image (game->mlx, (char *)filename,
			&img->width, &img->height);
	if (!img->mlx_img)
		return (FALSE);
	img->data = (void *)mlx_get_data_addr (img->mlx_img, &img->bits_per_px,
			&img->line_len, &img->endianness);
	if (!img->data)
		return (FALSE);
	return (TRUE);
}

t_rgba	img_get_px(t_img *img, t_int x, t_int y)
{
	t_s64	offset;
	t_trgb	pixel;

	ft_assert (x >= 0 && x < img->width,
		"img_get_px: x (%i) is out of range.", x);
	ft_assert (y >= 0 && y < img->height,
		"img_get_px: y (%i) is out of range.", y);
	offset = y * img->line_len + x * (img->bits_per_px / 8);
	pixel = *(t_trgb *)(img->data + offset);
	return (trgb_to_rgba (pixel));
}

void	img_set_px(t_img *img, t_int x, t_int y, t_rgba color)
{
	t_s64	offset;

	ft_assert (x >= 0 && x < img->width,
		"img_set_px: x (%i) is out of range.", x);
	ft_assert (y >= 0 && y < img->height,
		"img_set_px: y (%i) is out of range.", y);
	offset = y * img->line_len + x * (img->bits_per_px / 8);
	*(t_trgb *)(img->data + offset) = rgba_to_trgb (color);
}
