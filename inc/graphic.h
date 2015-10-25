/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/14 23:36:12 by adebray           #+#    #+#             */
/*   Updated: 2015/10/25 02:42:53 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

# include <GLFW/glfw3.h>

# define WIDTH 640
# define HEIGHT 640

GLFWwindow*		g_window;

typedef struct	s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;
//
// int		g_color_table[TEAM_NUMBER + 1] = {
// 	0x000000,
// 	0xAA3939,
// 	0x7A9F35,
// 	0x226666,
// 	0xffff00,
// 	0xffffff
// };

t_color g_color_table[TEAM_NUMBER + 1] = {
	{ 0, 0, 0 },
	{ 170, 57, 57 },
	{ 122, 159, 53 },
	{ 34, 102, 102 },
	{ 170, 132, 57 },
	{ 255, 255, 255 }
};

#endif
