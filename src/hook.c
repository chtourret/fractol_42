/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctourret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:20:34 by ctourret          #+#    #+#             */
/*   Updated: 2018/04/20 15:36:41 by ctourret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static inline void	dezoom_moins(t_env *aff)
{
	t_map c;

	aff->h /= 0.9;
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
}

static inline void	zoom_plus(t_env *aff)
{
	t_map c;

	aff->h *= 0.9;
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
}

static inline void	ft_moove(int keycode, t_env *aff)
{
	if (keycode == 124)
	{
		aff->x1 -= 0.5 * aff->h;
		aff->x2 -= 0.5 * aff->h;
	}
	if (keycode == 123)
	{
		aff->x1 += 0.5 * aff->h;
		aff->x2 += 0.5 * aff->h;
	}
	if (keycode == 125)
	{
		aff->y1 -= 0.5 * aff->h;
		aff->y2 -= 0.5 * aff->h;
	}
	if (keycode == 126)
	{
		aff->y1 += 0.5 * aff->h;
		aff->y2 += 0.5 * aff->h;
	}
}

int		key_hook(int keycode, t_env *aff)
{
	if (keycode == 53)
		exit(1);
	if (keycode == 69)
		zoom_plus(aff);
	if (keycode == 51)
		aff->test += (aff->test == 0) ? 1 : -1;
	if (keycode == 78)
		dezoom_moins(aff);
	if (keycode == 12)
		aff->iter_max += 2;
	if (keycode == 14)
		aff->iter_max -= 2;
	if (keycode == 71)
		init_mandel(aff);
	if (keycode == 38)
		init_julia(aff);
	if (keycode == 124 || keycode == 123 || keycode == 125 || keycode == 126)
		ft_moove(keycode, aff);
	if (keycode == 7)
		aff->color -= (aff->color > 0) ? 1 : 0;
	if (keycode == 8)
		aff->color += (aff->color < 8) ? 1 : 0;
	expose_hook(aff);
	return (0);
}

int		expose_hook(t_env *aff)
{
	ft_bzero(aff->img_str, WIN_Y * aff->s_l);
	if (aff->check_file == 1)
		julia(aff);
	else if (aff->check_file == 2)
		mandelbrot(aff);
	else if (aff->check_file == 3)
		tricorn(aff);
	else if (aff->check_file == 4)
		burning_ship(aff);
	mlx_put_image_to_window(aff->img_str, aff->win, aff->img, 0, 0);
	put_text(aff);
	return (0);
}
