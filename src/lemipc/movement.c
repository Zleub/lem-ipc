/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:44:46 by adebray           #+#    #+#             */
/*   Updated: 2015/10/22 02:15:57 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemipc.h>
#include <common.h>

struct s_direction	g_direction = {
	.up = { 0, -1 },
	.down = { 0, 1 },
	.left = { -1, 0 },
	.right = { 1, 0 }
};

typedef struct		s_stack
{
	struct s_msgbuf	msg;
	struct s_stack	*prev;
}					t_stack;

int		poll_msg(void)
{
	struct s_msgbuf	buf;
	t_stack	*stack;
	t_stack	*tmp;

	stack = NULL;
	errno = 0;
	printf("poll_msg\n");
	while (errno != ENOMSG)
	{
		msgrcv(g_msg.id, &buf, sizeof(struct s_data), g_player.team, IPC_NOWAIT);
		if (errno != ENOMSG)
		{
			if (stack != NULL)
			{
				tmp = (t_stack *)malloc(sizeof(t_stack));
				ft_bzero(tmp, sizeof(t_stack));
				ft_memcpy(&tmp->msg, &buf, sizeof(struct s_msgbuf));
				tmp->prev = stack;
				stack = tmp;
			}
			else
			{
				stack = (t_stack *)malloc(sizeof(t_stack));
				ft_bzero(stack, sizeof(t_stack));
				ft_memcpy(&stack->msg, &buf, sizeof(struct s_msgbuf));
			}
		}
	}

	int i = 0;
	int present = 0;
	while (stack != NULL)
	{
		i += 1;
		printf("%d -> %d:%d\n", i, stack->msg.data.x, stack->msg.data.y);
		if (stack->msg.data.x == g_player.position.x && stack->msg.data.y == g_player.position.y)
			present = 1;
		// else if (move_to_buddies())
		// 	return (1);

		tmp = stack;
		stack = stack->prev;
		// msgsnd(g_msg.id, &tmp->msg, sizeof(struct s_data), 0);
		free(tmp);
	}
	return (present && i);
}

void	discuss(void)
{
	struct s_msgbuf		buf;
	buf.mtype = g_player.team;
	buf.data.x = g_player.position.x;
	buf.data.y = g_player.position.y;

	allocate_ressource(MSGQ_ACCESS);
	if (!poll_msg())
		msgsnd(g_msg.id, &buf, sizeof(struct s_data), 0);
	release_ressource(MSGQ_ACCESS);
	// struct s_msgbuf		buf;
	//
	// msgrcv(g_msg.id, &buf, sizeof(struct s_data), g_player.team, IPC_NOWAIT);
	// if (errno == ENOMSG)
	// 	errno = 0;
	// else
	// 	printf("buf: %d, %d\n", buf.data.x, buf.data.y);
}

void	move(struct s_point *direction)
{
	int index;
	int new_index;

	if ((g_player.position.x + direction->x < 0
			|| g_player.position.x + direction->x >= g_shm.size)
		|| (g_player.position.y + direction->y < 0
			|| g_player.position.y + direction->y >= g_shm.size))
		return ;
	index = g_player.position.x + g_player.position.y * g_shm.size;
	new_index = (g_player.position.x + direction->x) +
		(g_player.position.y + direction->y) * g_shm.size;
	if (g_shm.data[new_index] != 0)
	{
		// discuss();
		// printf("already someone\n");
		return ;
	}
	g_shm.data[index] = 0;
	g_player.position.x += direction->x;
	g_player.position.y += direction->y;
	index = NORMALIZE(g_player.position.x, g_player.position.y);
	g_shm.data[index] = g_player.team;
}

void	do_movement(char *buf)
{
	if (death() >= 2)
	{
		printf("I died\n");
		leave(0);
	}
	allocate_ressource(MAP_ACCESS);
	if (!ft_strcmp(buf, "up"))
		move(&g_direction.up);
	if (!ft_strcmp(buf, "down"))
		move(&g_direction.down);
	if (!ft_strcmp(buf, "left"))
		move(&g_direction.left);
	if (!ft_strcmp(buf, "right"))
		move(&g_direction.right);
	release_ressource(MAP_ACCESS);
}
