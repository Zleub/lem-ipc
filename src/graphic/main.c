/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 03:23:31 by adebray           #+#    #+#             */
/*   Updated: 2015/10/26 04:06:15 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>
#include <graphic.h>
#include <sys/time.h>
#include <math.h>

int				update(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glBegin(GL_QUADS);
	draw_world();
	glEnd();
	glFlush();
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
	g_animations = (double *)malloc(sizeof(double) * (g_shm.size * g_shm.size));
	ft_bzero(g_animations, sizeof(g_animations));
}

int				main(int argc, char *argv[])
{
	init(argc, argv);
	printf("lem-ipc graphic running.\n");
	if (!glfwInit())
		return (-1);
	g_window = glfwCreateWindow(WIDTH, HEIGHT, "lem-ipc", NULL, NULL);
	if (!g_window)
	{
		glfwTerminate();
		return (-1);
	}
	glfwMakeContextCurrent(g_window);
	g_timer = (M_PI * 2 * SLEEP_TIME) / 1000000;
	while (!glfwWindowShouldClose(g_window))
	{
		update();
		glfwSwapBuffers(g_window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
