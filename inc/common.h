/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/01 18:27:29 by adebray           #+#    #+#             */
/*   Updated: 2015/10/25 02:57:32 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <libft.h>

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>

# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/msg.h>

# define NORMALIZE(a, b) a + b * g_shm.size
# define MIN(x, y) ((x < y) ? x : y)
# define MAX(x, y) ((x > y) ? x : y)

# define SIZE 32
# define ID 42
# define PATH "./shared_segment"
# define SEM_PATH "./semaphore_set"

# define SLEEP_TIME (1000000 / 2)
# define TEAM_NUMBER 5

enum				e_sem
{
	MAP_ACCESS,
	SHMCTL_ACCESS,
	MSGQ_ACCESS
};

struct				s_ftok
{
	char			*path;
	int				id;
	key_t			key;
};

struct				s_shm
{
	int				size;
	int				id;
	char			*data;
};

struct				s_sem
{
	int				id;
};

struct				s_msg
{
	int				id;
};

enum				e_msgbuf
{
	TYPEA = 1
};

struct				s_msgbuf
{
	long			mtype;
	struct s_data
	{
		int		x;
		int		y;
	}				data;
};

struct s_ftok		g_ftok;
struct s_shm		g_shm;
struct s_sem		g_sem;
struct s_msg		g_msg;

void				init_common(void);
void				attach_shm(void);
void				interrupt(int sig);

void				allocate_ressource(int ressource);
void				release_ressource(int ressource);

#endif
