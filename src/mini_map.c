/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:26:37 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/19 22:20:06 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void    draw_ray(t_data *data, float x2, float y2, int color)
{
	float x;
	float y;
	float dx, dy, step;
	int i;
color = 0;
	dx = (x2 - data->player.x * SIZE_ - SIZE_PLYR / 2);
	dy = (y2 - data->player.y * SIZE_ - SIZE_PLYR / 2);
	if (fabsf(dx) >= fabsf(dy))
		step = fabsf(dx);
	else
		step = fabsf(dy);
	dx = dx / step;
	dy = dy / step;
	x = data->player.x * SIZE_ + SIZE_PLYR / 2;
	y = data->player.y * SIZE_ + SIZE_PLYR / 2;
	i = 1;
	while (i <= step)
	{
		put_pixel(data, data->addr, COL_PLAYER, x, y, 0);
		x = x + dx;
		y = y + dy;
		i = i + 1;
	}
}

void	draw_player(t_data *data, t_ray *ray, int x, int y, int status)
{
	int i;
	int j;

	i = x,
	j = y;
	while (j < y + SIZE_PLYR)
	{
		i = x;
		while (i < x + SIZE_PLYR)
			put_pixel(data, data->addr, COL_PLAYER, i++, j, 0);
		j++;
	}
	while (ray)
	{
		draw_ray(data, ray->x, ray->y, status);
		ray = ray->next;
	}
}

void	draw_mini_map(t_data *data)
{
	int v_limit;
	int h_limit;
	int i;
	int j;
	int h = 0;
	int v = 0;

	j = 0;
	v_limit = SIZE_;
	while (v + 1 < data->mapLen * SIZE_)
	{
		h = 0;
		i = 0;
		h_limit = SIZE_;
		while (h + 1 < (int)ft_strlen(data->map[j]) * SIZE_)
		{
			if (data->map[j][i] == '1')
				put_pixel(data, data->addr, 0x282828, h, v, 0);
			else if (data->map[j][i] == '0' || is_player((data->map[j][i])))
				put_pixel(data, data->addr, 0xCCCCCC, h, v, 0);
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

void	draw_moved_mini_map(t_data *data)
{
	int v_limit;
	int h_limit;
	int i;
	int j;
	int h = 0;
	int v = 0;

	j = (int)data->player.y - (MINI_MAP_HEIGHT/2);
	v_limit = SIZE_;
	while (v < SIZE_ * MINI_MAP_HEIGHT)
	{
		h = 0;
		i = (int)data->player.x - (MINI_MAP_WIDTH/2);
		h_limit = SIZE_;
		while (h < SIZE_ * MINI_MAP_WIDTH)
		{
			if (point_in_range(data, i, j))
			{
				if (data->map[j][i] == '1')
					put_pixel(data, data->addr, 0x282828, h, v, 0);
				else if (data->map[j][i] != ' ' && data->map[j][i] != '1')
					put_pixel(data, data->addr, 0xCCCCCC, h, v, 0);
			}
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
	// if (data->row <= 13)
	// {
		draw_mini_map(data);
		draw_player(data, ray, data->player.x * SIZE_,data->player.y * SIZE_, 0);
		
	// }
	// else
	// {
	// 	draw_moved_mini_map(data);
	// 	draw_player(data, ray, SIZE_ * MINI_MAP_WIDTH / 2 + SIZE_ / 2, SIZE_ * MINI_MAP_HEIGHT / 2 + SIZE_ / 2, 1);
	// }
}