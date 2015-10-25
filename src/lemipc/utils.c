/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 22:14:21 by adebray           #+#    #+#             */
/*   Updated: 2015/10/18 19:59:48 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lemipc.h>
#include <common.h>

static void		sort_int_tab(int *tab, int size)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (tab[i] > tab[i + 1])
		{
			j = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = j;
			i = 0;
		}
		else
			i += 1;
	}
}

int				death(void)
{
	int		tmp_x;
	int		tmp_y;
	int		tmp;
	int		cmp[8];

	tmp_x = -1;
	ft_bzero(cmp, sizeof(cmp));
	while (tmp_x <= 1)
	{
		tmp_y = -1;
		while (tmp_y <= 1)
		{
			if ((PLAYER_X >= 0 && PLAYER_X < g_shm.size)
				&& (PLAYER_Y >= 0 && PLAYER_Y < g_shm.size))
			{
				tmp = g_shm.data[PLAYER_X + PLAYER_Y * g_shm.size];
				if (tmp && tmp != g_player.team)
					cmp[tmp] += 1;
			}
			tmp_y += 1;
		}
		tmp_x += 1;
	}
	sort_int_tab(cmp, 8);
	return (cmp[7]);
}

static void		lemipc_usage(void)
{
	write(1, "Usage: -i [ftok_id] -p [ftok_path] -s [shm_size]", 48);
	write(1, " -t [team_number] -x [number] -y [number]\n", 43);
	exit(-1);
}

void			init(int argc, char *argv[])
{
	int	ch;

	init_common();
	while ((ch = getopt(argc, argv, "s:t:x:y:")) != -1)
	{
		if (ch == '?')
			lemipc_usage();
		else if (ch == 's')
			g_shm.size = ft_atoi(optarg);
		else if (ch == 't')
			g_player.team = ft_atoi(optarg);
		else if (ch == 'x')
			g_player.position.x = ft_atoi(optarg);
		else if (ch == 'y')
			g_player.position.y = ft_atoi(optarg);
	}
	if (!g_ftok.id || !g_shm.size || !g_player.team)
		lemipc_usage();
	attach_shm();
	signal(SIGINT, &leave);
	signal(SIGKILL, &leave);
	signal(SIGTERM, &leave);
}
