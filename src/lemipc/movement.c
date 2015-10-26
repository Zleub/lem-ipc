/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:44:46 by adebray           #+#    #+#             */
/*   Updated: 2015/10/26 04:10:58 by adebray          ###   ########.fr       */
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

void	send_message(void)
{
	struct s_msgbuf		buf;

	buf.mtype = TYPEA;
	buf.data.x = g_player.position.x;
	buf.data.y = g_player.position.y;
	msgsnd(g_msg.id, &buf, sizeof(struct s_data), 0);
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
		return ;
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
		send_message();
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
