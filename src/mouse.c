/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctourret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:29:44 by ctourret          #+#    #+#             */
/*   Updated: 2017/05/19 16:59:10 by ctourret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

long double		ft_remap(t_map c)
{
	long double ret;

	ret = ((c.x - c.in_min) * (c.out_max - c.out_min) / (c.in_max - c.in_min)
			+ c.out_min);
	return (ret);
}

int				mouse_moove(int x, int y, t_env *aff)
{
	t_map mx;
	t_map my;

	if (aff->test == 1)
	{
		mx.in_min = 0;
		mx.in_max = WIN_X;
		mx.out_min = -2.1;
		mx.out_max = 0.6;
		mx.x = x;
		aff->c_r = ft_remap(mx);
		my.in_min = 0;
		my.in_max = WIN_Y;
		my.out_min = -1.2;
		my.out_max = 1.2;
		my.x = y;
		aff->c_i = ft_remap(my);
	}
	expose_hook(aff);
	return (0);
}

static inline void		m_zoom_in(t_env *aff, int x, int y)
{
	t_map c;

	aff->h *= 0.9;
	c.out_min = aff->x1;
	c.out_max = aff->x2;
	c.in_min = 0;
	c.in_max = WIN_X;
	c.x = x;
	aff->xu = ft_remap(c);
	c.out_min = aff->y1;
	c.out_max = aff->y2;
	c.in_min = 0;
	c.in_max = WIN_Y;
	c.x = y;
	aff->yu = ft_remap(c);
	aff->x1 = aff->xu - aff->h;
	aff->x2 = aff->xu + aff->h;
	aff->y1 = aff->yu - aff->h;
	aff->y2 = aff->yu + aff->h;
	aff->iter_max += 1;
}

static inline void		m_zoom_out(t_env *aff, int x, int y)
{
	t_map c;

	aff->h /= 0.9;
	c.out_min = aff->x1;
	c.out_max = aff->x2;
	c.in_min = 0;
	c.in_max = WIN_X;
	c.x = x;
	aff->xu = ft_remap(c);
	c.out_min = aff->y1;
	c.out_max = aff->y2;
	c.in_min = 0;
	c.in_max = WIN_Y;
	c.x = y;
	aff->yu = ft_remap(c);
	aff->x1 = aff->xu - aff->h;
	aff->x2 = aff->xu + aff->h;
	aff->y1 = aff->yu - aff->h;
	aff->y2 = aff->yu + aff->h;
}

int				mouse_zoom(int button, int x, int y, t_env *aff)
{
	if (button == 1)
		m_zoom_in(aff, x, y);
	if (button == 2)
		m_zoom_out(aff, x, y);
	expose_hook(aff);
	return (0);
}
