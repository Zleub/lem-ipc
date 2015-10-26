/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/26 03:53:36 by adebray           #+#    #+#             */
/*   Updated: 2015/10/26 04:07:20 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>
#include <graphic.h>
#include <math.h>

void			fill_animation(int x, int y)
{
	int i;
	int j;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			if ((x + i > 0 && x + i < g_shm.size)
				&& (y + j > 0 && y + j < g_shm.size)
				&& (g_shm.data[(x + i) + (y + j) * g_shm.size]))
				g_animations[(x + i) + (y + j) * g_shm.size] = M_PI * 2;
			j += 1;
		}
		i += 1;
	}
}

void			poll_msg(void)
{
	struct s_msgbuf	buf;

	errno = 0;
	while (errno != ENOMSG)
	{
		msgrcv(g_msg.id, &buf, sizeof(struct s_data), TYPEA, IPC_NOWAIT);
		if (errno != ENOMSG)
		{
			allocate_ressource(MAP_ACCESS);
			fill_animation(buf.data.x, buf.data.y);
			release_ressource(MAP_ACCESS);
		}
	}
}
