/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:26:37 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/09 08:32:41 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_ray(t_data *data, float Bx, float By)
{
	float Ax = data->player.x * SIZE_ + SIZE_PLYR / 2;
	float Ay = data->player.y * SIZE_ + SIZE_PLYR / 2;
	float dx = Bx - Ax;
	float dy = By - Ay;
	float step;
	float i = 0;

	if (dx >= dy)
		step = fabs(dx);
	else
		step = fabs(dy);
	while (i < step)
	{
		Ax += dx / step;
		Ay += dy / step;
		put_pixel(data, COL_PLAYER, (int)Ax, (int)Ay, 0);
		i++;
	}
}

void	draw_player(t_data *data, t_ray *ray)
{
	int i;
	int j;

	i = data->player.x * SIZE_;
	j = data->player.y * SIZE_;
	while (j < data->player.y * SIZE_ + SIZE_PLYR)
	{
		i = data->player.x * SIZE_;
		while (i < data->player.x * SIZE_ + SIZE_PLYR)
			put_pixel(data, COL_PLAYER, i++, j, 0);
		j++;
	}
	draw_ray(data, ray->x, ray->y);
	while (ray->next)
		ray = ray->next;
	draw_ray(data, ray->x, ray->y);
}

void	draw_mini_map(t_data *data)
{
	int v_limit;
	int h_limit;
	int i;
	int j;
	int h = 0;
	int v = 0;
	int color;

	j = 0;
	v_limit = SIZE_;
	while (v < data->row * SIZE_)
	{
		h = 0;
		i = 0;
		h_limit = SIZE_;
		while (h < data->col * SIZE_)
		{
			if (data->map[j][i] == '1')
				color = 0x444444;
			else
				color = 0xffffff;
			put_pixel(data, color, h, v, 0);
			h++;
			if (h >= h_limit)
			{
				i++;
				h_limit += SIZE_;
			}
		}
		v++;
		if (v >= v_limit)
		{
			j++;
			v_limit += SIZE_;
		}
	}
}

void mini_map(t_data *data, t_ray *ray)
{
	draw_mini_map(data);
	draw_player(data, ray);
}