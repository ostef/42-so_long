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
	"File error: ",
	"Memory error.",
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
	ft_assert (err > 0 && err < ERR_COUNT, "Invalid error code %i.", err);
	ft_fprint (STDERR, g_error_strs[err]);
	if (err == ERR_FILE)
		ft_fprint (STDERR, strerror (errno));
	ft_fprint (STDERR, "\n");
}
