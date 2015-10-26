/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 03:29:20 by adebray           #+#    #+#             */
/*   Updated: 2015/10/26 04:14:05 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>
#include <graphic.h>
#include <sys/time.h>
#include <math.h>

t_color g_color_table[TEAM_NUMBER + 1] = {
	{ 0, 0, 0 },
	{ 170, 57, 57 },
	{ 122, 159, 53 },
	{ 34, 102, 102 },
	{ 170, 132, 57 },
	{ 255, 255, 255 }
};

void	rotate(t_point *p, t_point c, double theta)
{
	double tmp;

	tmp = p->x;
	p->x = (cosf(theta) * (p->x - c.x) - sinf(theta) * (p->y - c.y)) + c.x;
	p->y = (sinf(theta) * (tmp - c.x) + cosf(theta) * (p->y - c.y)) + c.y;
}

void	rotate_square(t_square *s, double rotation)
{
	rotate(&s->p1, s->center, rotation);
	rotate(&s->p2, s->center, rotation);
	rotate(&s->p3, s->center, rotation);
	rotate(&s->p4, s->center, rotation);
}

void	fill_square(int i, int j, t_square *square)
{
	double	w;
	double	h;

	w = 2.0f / g_shm.size;
	h = 2.0f / g_shm.size;
	square->p1.x = (i - g_shm.size / 2) * w;
	square->p1.y = (j - g_shm.size / 2) * h;
	square->p2.x = (i - g_shm.size / 2) * w + (w * 0.9f);
	square->p2.y = (j - g_shm.size / 2) * h;
	square->p3.x = (i - g_shm.size / 2) * w + (w * 0.9f);
	square->p3.y = (j - g_shm.size / 2) * h + (h * 0.9f);
	square->p4.x = (i - g_shm.size / 2) * w;
	square->p4.y = (j - g_shm.size / 2) * h + (h * 0.9f);
	square->center.x = square->p1.x + w / 2;
	square->center.y = square->p1.y + h / 2;
}

void	draw_player(int i, int j)
{
	int			data;
	t_square	square;

	data = g_shm.data[i + j * g_shm.size];
	if (data != 0)
	{
		fill_square(i, j, &square);
		if (g_animations[i + j * g_shm.size] > 0)
		{
			rotate_square(&square, g_animations[i + j * g_shm.size]);
			g_animations[i + j * g_shm.size] -= M_PI / g_timer;
		}
		glColor3f(g_color_table[data].r / 255.0f,
			g_color_table[data].g / 255.0f, g_color_table[data].b / 255.0f);
		glVertex2f(square.p1.x, square.p1.y);
		glVertex2f(square.p2.x, square.p2.y);
		glVertex2f(square.p3.x, square.p3.y);
		glVertex2f(square.p4.x, square.p4.y);
	}
	else if (g_animations[i + j * g_shm.size] > 0)
		g_animations[i + j * g_shm.size] = 0;
}

void	draw_world(void)
{
	int			i;
	int			j;

	i = 0;
	poll_msg();
	while (i < g_shm.size)
	{
		j = 0;
		while (j < g_shm.size)
		{
			draw_player(i, j);
			j += 1;
		}
		i += 1;
	}
}
