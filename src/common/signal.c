/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 22:32:31 by adebray           #+#    #+#             */
/*   Updated: 2015/10/18 21:38:19 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

void		interrupt(int sig)
{
	struct shmid_ds	buf;

	(void)sig;
	allocate_ressource(SHMCTL_ACCESS);
	shmctl(g_shm.id, IPC_STAT, &buf);
	printf("this is interrupt %d\n", buf.shm_nattch);
	if (buf.shm_nattch == 1)
	{
		shmctl(g_shm.id, IPC_RMID, NULL);
		semctl(g_sem.id, 0, IPC_RMID);
		msgctl(g_msg.id, IPC_RMID, NULL);
	}
	exit(-1);
}
