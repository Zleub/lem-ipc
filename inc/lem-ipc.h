/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-ipc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/01 18:27:29 by adebray           #+#    #+#             */
/*   Updated: 2015/10/01 18:57:16 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include <stdio.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 128
#define ID 42
#define PATH "./shared_segment"

struct				s_ftok
{
	char			*path;
	int				id;
	key_t			key;
};

struct				s_shm
{
	struct s_ftok	ftok;
	int				size;
	int				id;
	char			*data;
};

struct s_shm		g_shm;

void				init_shm(void);
void				attach_shm(void);
void				interrupt(int sig);
