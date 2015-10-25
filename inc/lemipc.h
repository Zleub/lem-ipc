/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemipc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:37:03 by adebray           #+#    #+#             */
/*   Updated: 2015/10/22 02:52:05 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIPC_H
# define LEMIPC_H

# include <time.h>

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_direction
{
	t_point		up;
	t_point		down;
	t_point		left;
	t_point		right;
}				t_direction;

typedef struct	s_player
{
	int			team;
	t_point		position;
}				t_player;

t_player		g_player;

# define NORMALIZE(a, b) a + b * g_shm.size
# define IS_ENEMY(number) (number != g_player.team) && (number != 0)
# define IS_UP_LEFTED(a, b) (a < g_shm.size / 2) && (b < g_shm.size / 2)
# define IS_DOWN_LEFTED(a, b) (a < g_shm.size / 2) && (b >= g_shm.size / 2)
# define IS_UP_RIGHTED(a, b) (a >= g_shm.size / 2) && (b < g_shm.size / 2)
# define IS_DOWN_RIGHTED(a, b) (a >= g_shm.size / 2) && (b >= g_shm.size / 2)
# define ABS(x) (x < 0 ? -x : x)
# define RANGE g_shm.size / 4
# define PLAYER_X (g_player.position.x + tmp_x)
# define PLAYER_Y (g_player.position.y + tmp_y)
# define IS_IN_MAP(x) (x >= 0 && x < g_shm.size)

int				death(void);
void			init(int argc, char *argv[]);
void			leave(int sig);
int				check_circle(t_point *res, int radius);
void			move(struct s_point *direction);
void			do_movement(char *buf);
int				check_line(t_point *res, t_point *pos, t_point *dir, int max);
void			build_corners(int radius, t_point array[4]);
int				check_circle(t_point *res, int radius);
int				test(t_point *res, struct s_point **dir, int cmp);

#endif
