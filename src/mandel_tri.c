/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_tri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctourret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:46:30 by ctourret          #+#    #+#             */
/*   Updated: 2017/05/19 16:58:54 by ctourret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void				init_mandel(t_env *aff)
{
	t_map c;

	aff->x1 = (aff->check_file == 1) ? -1 : -2.1;
	aff->x2 = (aff->check_file == 1) ? 1 : 0.6;
	aff->y1 = -1.2;
	aff->y2 = 1.2;
	aff->h = 1;
	c.out_min = aff->x1;
	c.out_max = aff->x2;
	c.in_min = 0;
	c.in_max = WIN_X;
	c.x = WIN_X / 2;
	aff->xu = ft_remap(c);
	c.out_min = aff->y1;
	c.out_max = aff->y2;
	c.in_min = 0;
	c.in_max = WIN_Y;
	c.x = WIN_Y / 2;
	aff->yu = ft_remap(c);
	aff->x1 = aff->xu - aff->h;
	aff->x2 = aff->xu + aff->h;
	aff->y1 = aff->yu - aff->h;
	aff->y2 = aff->yu + aff->h;
	aff->test = 1;
	aff->iter_max = 50;
}

static inline void	mandelbrot_tricorn_split(int *i, t_env *aff, int x, int y)
{
	double	z_r;
	double	z_i;
	double	tmp;

	aff->c_r = x / aff->zoom_x + aff->x1;
	aff->c_i = y / aff->zoom_y + aff->y1;
	z_r = x / aff->zoom_x + aff->x1;
	z_i = y / aff->zoom_y + aff->y1;
	while ((z_r * z_r) + (z_i * z_i) < 4 && *i < aff->iter_max)
	{
		tmp = z_r;
		z_r = (z_r * z_r) - (z_i * z_i) + aff->c_r;
		if (aff->flag == 1)
			z_i = 2 * z_i * tmp + aff->c_i;
		else
			z_i = -2 * z_i * tmp + aff->c_i;
		*i = *i + 1;
	}
	if (*i == aff->iter_max)
		ft_pixel_put(aff, x, y, 0x00000000);
	else
		ft_pixel_put(aff, x, y, ft_rgb(*i * 255 / aff->iter_max, aff->color));
}

void				mandelbrot(t_env *aff)
{
	int		x;
	int		y;
	int		i;

	aff->zoom_x = WIN_X / (aff->x2 - aff->x1);
	aff->zoom_y = WIN_Y / (aff->y2 - aff->y1);
	y = 0;
	aff->flag = 1;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			i = 0;
			mandelbrot_tricorn_split(&i, aff, x, y);
			x++;
		}
		y++;
	}
}

void				tricorn(t_env *aff)
{
	int		x;
	int		y;
	int		i;

	aff->zoom_x = WIN_X / (aff->x2 - aff->x1);
	aff->zoom_y = WIN_Y / (aff->y2 - aff->y1);
	aff->flag = 0;
	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			i = 0;
			mandelbrot_tricorn_split(&i, aff, x, y);
			x++;
		}
		y++;
	}
}
