/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/19 16:52:07 by adebray	          #+#    #+#             */
/*   Updated: 2015/10/25 02:59:12 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>
#include <graphic.h>
#include <sys/time.h>

int g_time;
int g_fps;
double *g_animations;
double g_timer;

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_square
{
	t_point			A;
	t_point			B;
	t_point			C;
	t_point			D;
	t_point			center; //?
}					t_square;

typedef struct		s_stack
{
	t_square		*s;
	struct s_stack	*next;
}					t_stack;

typedef struct		s_linear
{
	t_point			*A;
	t_point			*B;
	double			coef;
	double			ord;
}					t_linear;

t_stack				*g_stack = NULL;

void			push_stack(t_square *square)
{
	static t_stack	*last;
	t_stack		*s = (t_stack *)malloc(sizeof(t_stack));
	ft_bzero(s, sizeof(t_stack));
	s->s = square;

	if (!g_stack)
	{
		g_stack = s;
		last = s;
	}
	else
	{
		last->next = s;
		last = s;
	}
}

#include <math.h>

void rotate(t_point *p, t_point c, double theta)
{
	double tmp;

	tmp = p->x;
	p->x = (cosf(theta) * (p->x - c.x) - sinf(theta) * (p->y - c.y)) + c.x;
   	p->y = (sinf(theta) * (tmp - c.x) + cosf(theta) * (p->y - c.y)) + c.y;
}

void rotate_square(t_square *s, double rotation)
{
	rotate(&s->A, s->center, rotation);
	rotate(&s->B, s->center, rotation);
	rotate(&s->C, s->center, rotation);
	rotate(&s->D, s->center, rotation);
}

void	draw_stack(t_stack *s)
{
	if (!s)
		return ;
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(s->s->A.x, s->s->A.y);
	glVertex2f(s->s->B.x, s->s->B.y);
	glVertex2f(s->s->C.x, s->s->C.y);
	glVertex2f(s->s->D.x, s->s->D.y);
	draw_stack(s->next);
}

void	draw_world(void)
{
	int		i;
	int		j;
	double	w = 2.0f / g_shm.size;
	double	h = 2.0f / g_shm.size;

	i = 0;
	while (i < g_shm.size)
	{
		j = 0;
		while (j < g_shm.size)
		{
			int data = g_shm.data[i + j * g_shm.size];
			if (data != 0)
			{
				t_square square;

				square.A.x = (i - g_shm.size / 2) * w;
				square.A.y = (j - g_shm.size / 2) * h;
				square.B.x = (i - g_shm.size / 2) * w + (w * 0.9f);
				square.B.y = (j - g_shm.size / 2) * h;
				square.C.x = (i - g_shm.size / 2) * w + (w * 0.9f);
				square.C.y = (j - g_shm.size / 2) * h + (h * 0.9f);
				square.D.x = (i - g_shm.size / 2) * w;
				square.D.y = (j - g_shm.size / 2) * h + (h * 0.9f);
				square.center.x = square.A.x + w / 2;
				square.center.y = square.A.y + h / 2;

				// printf("%f, %f\n", square.center.x, square.center.y);

				if (g_animations[i + j * g_shm.size] > 0)
				{
					rotate_square(&square, g_animations[i + j * g_shm.size]);
					g_animations[i + j * g_shm.size] -= M_PI / g_timer;
				}

				glColor3f(g_color_table[data].r / 255.0f, g_color_table[data].g / 255.0f, g_color_table[data].b / 255.0f);
				glVertex2f(square.A.x, square.A.y);
				glVertex2f(square.B.x, square.B.y);
				glVertex2f(square.C.x, square.C.y);
				glVertex2f(square.D.x, square.D.y);

			}
			j += 1;
		}
		i += 1;
	}
}

int				update()
{
	static int  cmp;
	// rotate_square(g_stack->s, M_PI / 45);
	// rotate_square(g_stack->next->s, M_PI / 180);

	glClear( GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	    glBegin(GL_QUADS);

	    {
			// draw_stack(g_stack);
			draw_world();
	    }

	glEnd();
	glFlush();
	cmp += 1;

	int t = time(NULL);
	if (t != g_time)
	{
		g_fps = cmp;
		cmp = 0;
		g_time = t;
		printf("%d\n", g_fps);
	}

	return (0);
}

static void		usage(void)
{
	printf("Usage: -i [ftok_id] -p [ftok_path] -s [shm_size]\n");
	exit(-1);
}

void			init(int argc, char *argv[])
{
	int	ch;

	init_common();
	while ((ch = getopt(argc, argv, "i:s:")) != -1)
	{
		if (ch == '?')
			usage();
		else if (ch == 's')
			g_shm.size = ft_atoi(optarg);
	}
	if (!g_ftok.id || !g_shm.size)
		usage();
	attach_shm();
}

int				main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	init(argc, argv);

	// push_stack(&square);
	// push_stack(&square2);
	printf("lem-ipc graphic running.\n");

	g_animations = (double *)malloc(sizeof(double) * (g_shm.size * g_shm.size));
	ft_bzero(g_animations, sizeof(g_animations));
	g_animations[10 + 10 * g_shm.size] = M_PI * 2;

	if (!glfwInit())
		  return -1;
	g_window = glfwCreateWindow(WIDTH, HEIGHT, "lem-ipc", NULL, NULL);
	if (!g_window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(g_window);
	g_time = time(NULL);
	g_timer = (M_PI * 2 * SLEEP_TIME) / 1000000;
	while (!glfwWindowShouldClose(g_window))
    {
        /* Render here */

		update();

        /* Swap front and back buffers */
        glfwSwapBuffers(g_window);

        /* Poll for and process events */
        glfwPollEvents();
    }
	glfwTerminate();
	return (0);
}
