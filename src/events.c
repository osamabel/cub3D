/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:44:52 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/21 18:59:16 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	keyprelease(int keycode, void *parm)
{
	t_data	*data;

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
	return (0);
}

int	keypress(int keycode, void *parm)
{
	t_data	*data;

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
	if (keycode == 49)
		data->player.shoot = 1;
	if (keycode == 53)
		ft_exit(data, NULL);
	return (0);
}

int	mouse_hook(int x, int y, void *param)
{
	t_data		*data;
	static int	last_x;
	float		dx;

	data = (t_data *)param;
	dx = last_x - x;
	if (y > 0 && y < HEIGHT)
		data->player.mouse = atan(dx / data->mid_ray_d) * (0.4 + data->player.rotatespeed);
	last_x = x;
	return (0);
}
