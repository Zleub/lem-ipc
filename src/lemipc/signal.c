/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 22:13:50 by adebray           #+#    #+#             */
/*   Updated: 2015/10/18 21:38:30 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemipc.h>
#include <common.h>

void		leave(int sig)
{
	struct shmid_ds	buf;
	int				index;

	(void)sig;
	index = NORMALIZE(g_player.position.x, g_player.position.y);
	allocate_ressource(MAP_ACCESS);
	g_shm.data[index] = 0;
	release_ressource(MAP_ACCESS);
	allocate_ressource(SHMCTL_ACCESS);
	shmctl(g_shm.id, IPC_STAT, &buf);
	if (buf.shm_nattch == 1)
	{
		printf("I'm the last one, destoying ressources\n");
		shmctl(g_shm.id, IPC_RMID, NULL);
		semctl(g_sem.id, 0, IPC_RMID);
		msgctl(g_msg.id, IPC_RMID, NULL);
	}
	exit(-1);
}
