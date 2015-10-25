/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:45:49 by adebray           #+#    #+#             */
/*   Updated: 2015/10/17 23:46:25 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemipc.h>
#include <common.h>

extern struct s_direction	g_direction;

struct s_point		*look1[2] = {
	&g_direction.left,
	&g_direction.up
};

struct s_point		*look2[2] = {
	&g_direction.right,
	&g_direction.up
};

struct s_point		*look3[2] = {
	&g_direction.left,
	&g_direction.down
};

struct s_point		*look4[2] = {
	&g_direction.right,
	&g_direction.down
};

int		check_line(t_point *res, t_point *pos, t_point *dir, int max)
{
	int	index;
	int tmp_x;
	int tmp_y;

	tmp_x = pos->x;
	tmp_y = pos->y;
	while (tmp_x != max && tmp_y != max)
	{
		if (IS_IN_MAP(PLAYER_X) && IS_IN_MAP(PLAYER_Y))
		{
			index = NORMALIZE(PLAYER_X, PLAYER_Y);
			if (IS_ENEMY(g_shm.data[index]))
			{
				res->x = tmp_x;
				res->y = tmp_y;
				return (1);
			}
		}
		tmp_x += dir->x;
		tmp_y += dir->y;
	}
	return (0);
}

void	build_corners(int radius, t_point array[4])
{
	array[0].x = radius;
	array[0].y = radius;
	array[1].x = -radius;
	array[1].y = -radius;
	array[2].x = -radius;
	array[2].y = radius;
	array[3].x = radius;
	array[3].y = -radius;
}

int		check_circle(t_point *res, int radius)
{
	int				cmp;
	struct s_point	**dir;

	if (IS_UP_LEFTED(g_player.position.x, g_player.position.y))
		dir = look1;
	if (IS_UP_RIGHTED(g_player.position.x, g_player.position.y))
		dir = look2;
	if (IS_DOWN_LEFTED(g_player.position.x, g_player.position.y))
		dir = look3;
	if (IS_DOWN_RIGHTED(g_player.position.x, g_player.position.y))
		dir = look4;
	cmp = 1;
	while (cmp < radius)
	{
		if (test(res, dir, cmp))
			return (1);
		cmp += 1;
	}
	return (0);
}
