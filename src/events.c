/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:44:52 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/17 08:49:40 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	(< : 123)  (>  :124)
	(D : 2)  (A  :0)
	(W : 13)  (S  :1)
*/

int keyprelease(int keycode, void *parm)
{
	t_data *data;
	data = (t_data *)parm;
	if (keycode == 124)
		data->player.turndirection = 0;
	if (keycode == 123)
		data->player.turndirection = 0;
	if (keycode == 13)
		data->player.walkdirection = 0;
	if (keycode == 1)
		data->player.walkdirection = 0;
	if (keycode == 0)
		data->player.sidedirection = 0;
	if (keycode == 2)
		data->player.sidedirection = 0;
	return 0;
}

int keypress(int keycode, void *parm)
{
	t_data *data;

	data = (t_data *)parm;
	if (keycode == 124)
		data->player.turndirection = -1;
	if (keycode == 123)
		data->player.turndirection = 1;
	if (keycode == 13)
		data->player.walkdirection = 1;
	if (keycode == 1)
		data->player.walkdirection = -1;
	if (keycode == 0)
		data->player.sidedirection = 1;
	if (keycode == 2)
		data->player.sidedirection = -1;
	if (keycode == 53)
		exit(0);
	return 0;
}

int mouse_hook(int x,int y,void *param)
{
	t_data *data;
	static int last_x;
	float dx;
	data = (t_data *)param;
	dx = last_x - x;
	if (y > 0 && y < HEIGHT)
		data->player.mouse = atan(dx / data->ray_d) * (0.1 + data->player.rotatespeed);
	last_x = x;
	return 0;
}