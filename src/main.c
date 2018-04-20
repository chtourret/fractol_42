/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctourret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 15:37:25 by ctourret          #+#    #+#             */
/*   Updated: 2017/05/19 16:58:26 by ctourret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

static inline void	init_mlx(t_env *aff)
{
	aff->mlx = mlx_init();
	aff->win = mlx_new_window(aff->mlx, WIN_X, WIN_Y, "FDF");
	aff->img = mlx_new_image(aff->mlx, WIN_X, WIN_Y);
	aff->img_str = mlx_get_data_addr(aff->img, &(aff->bpp),
			&(aff->s_l), &(aff->endian));
}

static inline int	ft_check(int ac, char **av, t_env *aff)
{
	int i;

	if (ac == 2)
	{
		i = -1;
		while (av[++i])
		{
			if (ft_strcmp(av[i], "julia") == 0)
				aff->check_file = 1;
			else if (ft_strcmp(av[i], "mandelbrot") == 0)
				aff->check_file = 2;
			else if (ft_strcmp(av[i], "tricorn") == 0)
				aff->check_file = 3;
			else if (ft_strcmp(av[i], "burningship") == 0)
				aff->check_file = 4;
			else
				aff->check_file = 0;
		}
		if (aff->check_file != 0)
			return (1);
		else
			return (0);
	}
	else
		return (-1);
}

static inline void	ft_error_fractal(void)
{
	ft_putstr_fd("❌ Fractal available : julia, mandelbrot, ", 2);
	ft_putendl_fd("tricorn, burningship", 2);
	exit(1);
}

static inline void	ft_error(void)
{
	ft_putendl_fd("Usage : ./fractol fractal_name", 2);
	exit(1);
}

int		main(int ac, char **av)
{
	t_env	*aff;

	if (!(aff = (t_env *)malloc(sizeof(t_env))))
		return (-1);
	if (ft_check(ac, av, aff) == -1)
		ft_error();
	else if (ft_check(ac, av, aff) == 0)
		ft_error_fractal();
	else
	{
		init_mandel(aff);
		init_mlx(aff);
		mlx_put_image_to_window(aff->img_str, aff->win, aff->img, 0, 0);
		mlx_hook(aff->win, 2, 3, key_hook, aff);
		aff->img_int = (int*)aff->img_str;
		mlx_expose_hook(aff->win, expose_hook, aff);
		mlx_hook(aff->win, 17, (1L << 17), red_cross, aff);
		mlx_hook(aff->win, 5, (1L << 8), mouse_zoom, aff);
		mlx_hook(aff->win, 6, (1L << 6), mouse_moove, aff);
		mlx_loop(aff->mlx);
	}
	return (0);
}
