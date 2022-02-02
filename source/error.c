/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 14:52:32 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/02 15:22:29 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <errno.h>
#include <string.h>

static t_cstr	g_error_strs[] = {
	"Ok.",
	"Memory error: ",
	"File error: ",
	"MLX error.",
	"Could not load atlas image.",
	"Could not load font image.",
	"Map has invalid cell.",
	"Map is not enclosed by walls.",
	"Map is not rectangular.",
	"Map has no player.",
	"Map has multiple players.",
	"Map has no exit.",
	"Map has no collectible."
};

void	print_err(t_err err)
{
	t_cstr	err_str;

	ft_assert (err > 0 && err < ERR_COUNT, "Invalid error code %i.", err);
	err_str = g_error_strs[err];
	ft_fprint (STDERR, err_str);
	if (err_str[ft_strlen (err_str) - 2] == ':')
		ft_fprint (STDERR, strerror (errno));
	ft_fprint (STDERR, "\n");
}
