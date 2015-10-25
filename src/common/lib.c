/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/01 17:28:34 by adebray           #+#    #+#             */
/*   Updated: 2015/10/20 01:02:31 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

void			attach_sem_first(int sem_size)
{
	struct sembuf sb;

	sb.sem_num = 0;
	sb.sem_op = 1;
	sb.sem_flg = 0;
	while (sb.sem_num < sem_size)
	{
		if (semop(g_sem.id, &sb, 1) == -1)
			printf("semop error\n");
		else
			printf("init sem %d\n", sb.sem_num);
		sb.sem_num += 1;
	}
}

void			attach_sem_other(int sem_size)
{
	int				lock;
	union semun		param;
	struct semid_ds	buf;

	param.buf = &buf;
	g_sem.id = semget(g_ftok.key, sem_size, 0666);
	if (g_sem.id < 0)
		printf("TEST ERROR\n");
	lock = 1;
	while (lock)
	{
		semctl(g_sem.id, 0, IPC_STAT, param);
		if (param.buf->sem_otime != 0)
			lock = 0;
		printf("waiting\n");
		usleep(SLEEP_TIME);
	}
}

void			attach_sem(void)
{
	int			sem_size;

	sem_size = 4;
	g_sem.id = semget(g_ftok.key, sem_size, 0666 | IPC_CREAT | IPC_EXCL);
	if (g_sem.id >= 0)
		attach_sem_first(sem_size);
	else if (errno == EEXIST)
		attach_sem_other(sem_size);
}

void			attach_shm(void)
{
	g_ftok.key = ftok(g_ftok.path, g_ftok.id);
	g_shm.id = shmget(g_ftok.key, g_shm.size * g_shm.size, 0644 | IPC_CREAT);
	g_shm.data = shmat(g_shm.id, NULL, 0);
	attach_sem();
	g_msg.id = msgget(g_ftok.key, 0666 | IPC_CREAT);
	printf("id: %d, path: %s, size: %d\n", g_ftok.id, g_ftok.path, g_shm.size);
	printf("shmid: %d, semid: %d\n", g_shm.id, g_sem.id);
	signal(SIGINT, &interrupt);
	signal(SIGKILL, &interrupt);
	signal(SIGTERM, &interrupt);
}

void			init_common(void)
{
	g_ftok.id = ID;
	g_ftok.path = PATH;
	g_shm.size = SIZE;
}
