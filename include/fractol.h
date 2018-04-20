/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctourret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 10:45:03 by ctourret          #+#    #+#             */
/*   Updated: 2017/05/31 15:51:37 by ctourret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <stdlib.h>
# include <math.h>
# include "../minilibx_macos/mlx.h"
# include "../libft/include/libft.h"
# define WIN_X		800
# define WIN_Y		700

typedef struct			s_map
{
	int				x;
	long double		in_min;
	long double		in_max;
	long double		out_min;
	long double		out_max;
}						t_map;

typedef struct			s_env
{
	char			*img_str;
	int				*img_int;
	void			*mlx;
	void			*win;
	void			*img;
	int				bpp;
	int				s_l;
	int				endian;
	double			zoom_x;
	double			zoom_y;
	int				x;
	int				y;
	double			x2;
	double			x1;
	double			y1;
	double			y2;
	double			z_r;
	double			z_i;
	double			c_r;
	double			c_i;
	int				iter_max;
	double			h;
	int				color;
	int				test;
	int				flag;
	int				check_file;
	long double		xu;
	long double		yu;
}						t_env;

int						expose_hook(t_env *aff);
int						mouse_zoom(int button, int x, int y, t_env *aff);
int						mouse_moove(int x, int y, t_env *aff);
int						red_cross(int key);
int						ft_rgb(int nb, int opt);
int						key_hook(int keycode, t_env *aff);
int						expose_hook(t_env *aff);
void					ft_pixel_put(t_env *aff, int x, int y, int color);
void					put_text(t_env *data);
void					init_mandel(t_env *aff);
void					mandelbrot(t_env *aff);
void					tricorn(t_env *aff);
void					julia(t_env *aff);
void					burning_ship(t_env *aff);
void					init_julia(t_env *aff);
long double				ft_remap(t_map c);

#endif
