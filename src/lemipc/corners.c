/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corners.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/17 23:16:11 by adebray           #+#    #+#             */
/*   Updated: 2015/10/17 23:30:22 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemipc.h>
#include <common.h>

static int	up_lefted_look(t_point *res, struct s_point **dir, int cmp)
{
	t_point		corners[4];

	build_corners(cmp, corners);
	return (check_line(res, &corners[0], dir[0], -cmp - 1) ||
		check_line(res, &corners[0], dir[1], -cmp - 1) ||
		check_line(res, &corners[3], dir[0], -cmp - 1) ||
		check_line(res, &corners[2], dir[1], -cmp - 1));
}

static int	up_righted_look(t_point *res, struct s_point **dir, int cmp)
{
	t_point		corners[4];

	build_corners(cmp, corners);
	return (check_line(res, &corners[2], dir[0], cmp + 1) ||
		check_line(res, &corners[2], dir[1], -cmp - 1) ||
		check_line(res, &corners[1], dir[0], cmp + 1) ||
		check_line(res, &corners[0], dir[1], -cmp - 1));
}

static int	down_lefted_look(t_point *res, struct s_point **dir, int cmp)
{
	t_point		corners[4];

	build_corners(cmp, corners);
	return (check_line(res, &corners[3], dir[0], -cmp - 1) ||
		check_line(res, &corners[3], dir[1], cmp + 1) ||
		check_line(res, &corners[0], dir[0], -cmp - 1) ||
		check_line(res, &corners[1], dir[1], cmp + 1));
}

static int	down_righted_look(t_point *res, struct s_point **dir, int cmp)
{
	t_point		corners[4];

	build_corners(cmp, corners);
	return (check_line(res, &corners[1], dir[0], cmp + 1) ||
		check_line(res, &corners[1], dir[1], cmp + 1) ||
		check_line(res, &corners[2], dir[0], cmp + 1) ||
		check_line(res, &corners[3], dir[1], cmp + 1));
}

int			test(t_point *res, struct s_point **dir, int cmp)
{
	if (IS_UP_LEFTED(g_player.position.x, g_player.position.y))
		return (up_lefted_look(res, dir, cmp));
	if (IS_UP_RIGHTED(g_player.position.x, g_player.position.y))
		return (up_righted_look(res, dir, cmp));
	if (IS_DOWN_LEFTED(g_player.position.x, g_player.position.y))
		return (down_lefted_look(res, dir, cmp));
	if (IS_DOWN_RIGHTED(g_player.position.x, g_player.position.y))
		return (down_righted_look(res, dir, cmp));
	return (0);
}
