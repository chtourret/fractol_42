/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_ship.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctourret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:43:09 by ctourret          #+#    #+#             */
/*   Updated: 2017/05/19 16:58:08 by ctourret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static inline void	julia_split(int *i, t_env *aff, int x, int y)
{
	double	tmp;
	double	z_r;
	double	z_i;

	z_r = x / aff->zoom_x + aff->x1;
	z_i = y / aff->zoom_y + aff->y1;
	while ((z_r * z_r) + (z_i * z_i) < 4 && *i < aff->iter_max)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + aff->c_r;
		z_i = 2 * z_i * tmp + aff->c_i;
		*i = *i + 1;
	}
	if (*i == aff->iter_max)
		ft_pixel_put(aff, x, y, 0x00000000);
	else
		ft_pixel_put(aff, x, y, ft_rgb(*i * 255 / aff->iter_max, aff->color));
}

void				julia(t_env *aff)
{
	int		i;
	int		y;
	int		x;

	aff->zoom_x = WIN_X / (aff->x2 - aff->x1);
	aff->zoom_y = WIN_Y / (aff->y2 - aff->y1);
	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			i = 0;
			julia_split(&i, aff, x, y);
			x++;
		}
		y++;
	}
}

static inline void	burningship_split(int *i, t_env *aff)
{
	double	tmp;
	double	z_r;
	double	z_i;

	aff->c_r = aff->x / aff->zoom_x + aff->x1;
	aff->c_i = aff->y / aff->zoom_y + aff->y1;
	z_r = aff->x / aff->zoom_x + aff->x1;
	z_i = aff->y / aff->zoom_y + aff->y1;
	while ((z_r * z_r) + (z_i * z_i) < 4 && *i < aff->iter_max)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + aff->c_r;
		z_i = 2 * z_i * tmp + aff->c_i;
		z_r = fabsl(z_r);
		z_i = fabsl(z_i);
		*i = *i + 1;
	}
	if (*i == aff->iter_max)
		ft_pixel_put(aff, aff->x, aff->y, 0x00000000);
	else
		ft_pixel_put(aff, aff->x, aff->y, ft_rgb(*i * 255 / aff->iter_max,
					aff->color));
}

void				burning_ship(t_env *aff)
{
	int		i;

	aff->zoom_x = WIN_X / (aff->x2 - aff->x1);
	aff->zoom_y = WIN_Y / (aff->y2 - aff->y1);
	aff->y = 0;
	while (aff->y < WIN_Y)
	{
		aff->x = 0;
		while (aff->x < WIN_X)
		{
			i = 0;
			burningship_split(&i, aff);
			aff->x++;
		}
		aff->y++;
	}
}

void				init_julia(t_env *aff)
{
	aff->x1 = -1;
	aff->x2 = 1;
	aff->y1 = -1.2;
	aff->y2 = 1.2;
	aff->c_r = 0.285;
	aff->c_i = 0.01;
}
