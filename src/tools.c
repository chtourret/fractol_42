/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctourret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:27:55 by ctourret          #+#    #+#             */
/*   Updated: 2017/05/19 16:59:26 by ctourret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int						red_cross(int key)
{
	key = (int)key;
	exit(0);
	return (0);
}

void					ft_pixel_put(t_env *aff, int x, int y, int color)
{
	int		res;

	res = (y * WIN_X) + x;
	if ((y > 0 && y < WIN_Y) && (x > 0 && x < WIN_X))
		aff->img_int[res] = color;
}

void	put_text(t_env *data)
{
	char	*text;
	char	*nb;

	nb = ft_itoa(data->iter_max);
	text = ft_strjoin("iterations : ", nb);
	mlx_string_put(data->mlx, data->win, 10, 10, 0xFFFFFF, text);
	ft_strdel(&text);
	ft_strdel(&nb);
}

static inline int		ft_rgb_2(int nb, int opt, int tmp)
{
	if (opt == 1)
	{
		tmp = nb;
		nb += nb << 9;
		nb += tmp << 19;
	}
	else if (opt == 2)
	{
		tmp = nb;
		nb += nb << 8;
		nb += tmp << 18;
	}
	else if (opt == 3)
	{
		tmp = nb;
		nb += nb << 7;
		nb += tmp << 17;
	}
	return (nb);
}

int						ft_rgb(int nb, int opt)
{
	int tmp;

	tmp = 0;
	if (opt >= 1 && opt <= 3)
		return (ft_rgb_2(nb, opt, tmp));
	else if (opt == 4)
	{
		tmp = nb;
		nb += nb << 1;
		nb += tmp << 11;
	}
	else if (opt == 5)
	{
		tmp = nb;
		nb += nb << 10;
		nb += tmp << 20;
	}
	else if (opt == 6)
	{
		tmp = nb;
		nb += nb << 8;
		nb += tmp << 16;
	}
	return (nb);
}
