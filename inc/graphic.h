/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:36:12 by adebray           #+#    #+#             */
/*   Updated: 2015/10/26 04:14:44 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include <GLFW/glfw3.h>

# define WIDTH 1280
# define HEIGHT 1280

GLFWwindow			*g_window;

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_square
{
	t_point			p1;
	t_point			p2;
	t_point			p3;
	t_point			p4;
	t_point			center;
}					t_square;

typedef struct		s_linear
{
	t_point			*p1;
	t_point			*p2;
	double			coef;
	double			ord;
}					t_linear;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

int					g_time;
int					g_fps;
double				*g_animations;
double				g_timer;

void				draw_world(void);
void				poll_msg(void);

#endif
