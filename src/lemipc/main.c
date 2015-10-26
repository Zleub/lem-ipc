/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/01 18:39:04 by adebray           #+#    #+#             */
/*   Updated: 2015/10/26 03:34:16 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemipc.h>
#include <common.h>

void	look_around(void)
{
	static int	radius;
	t_point		destination;

	if (!radius)
		radius = RANGE;
	if (check_circle(&destination, radius))
	{
		if (MAX(ABS(destination.x), ABS(destination.y)) == ABS(destination.x))
		{
			if (destination.x > 0)
				do_movement("right");
			else
				do_movement("left");
		}
		else
		{
			if (destination.y > 0)
				do_movement("down");
			else
				do_movement("up");
		}
		radius = 0;
	}
	else
		radius += RANGE;
}

void	do_move(void)
{
	look_around();
}

int		main(int argc, char *argv[])
{
	int		index;

	init(argc, argv);
	if (g_verbose)
		printf("This is a lem-ipc\n");
	srand((unsigned int)&g_player);
	if (!g_player.position.x)
		g_player.position.x = rand() % g_shm.size;
	if (!g_player.position.y)
		g_player.position.y = rand() % g_shm.size;
	index = NORMALIZE(g_player.position.x, g_player.position.y);
	allocate_ressource(MAP_ACCESS);
	g_shm.data[index] = g_player.team;
	release_ressource(MAP_ACCESS);
	while (42)
	{
		do_move();
		usleep(SLEEP_TIME);
	}
	leave(0);
	return (0);
}
