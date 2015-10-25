/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ressource_mgt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 22:29:33 by adebray           #+#    #+#             */
/*   Updated: 2015/10/18 21:10:35 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <common.h>

void		allocate_ressource(int ressource)
{
	struct sembuf sb;

	sb.sem_num = ressource;
	sb.sem_op = -1;
	sb.sem_flg = SEM_UNDO;
	if (semop(g_sem.id, &sb, 1) == -1)
		printf("Warning semop 31\n");
}

void		release_ressource(int ressource)
{
	struct sembuf sb;

	sb.sem_num = ressource;
	sb.sem_op = 1;
	sb.sem_flg = SEM_UNDO;
	if (semop(g_sem.id, &sb, 1) == -1)
		printf("Warning semop 41\n");
}
