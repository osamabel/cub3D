/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:10:30 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/08 10:59:41 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_background(t_data *data)
{
	int pixel;
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
			pixel = (v * data->line_length) + (h * 4);
			data->addr[pixel + 0] = (color) & 0xFF;
			data->addr[pixel + 1] = (color >> 8) & 0xFF;
			data->addr[pixel + 2] = (color >> 16) & 0xFF;
			data->addr[pixel + 3] = (color >> 24);
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

void	draw_xray(t_data *data, float Bx, float By)
{
	float Ax = data->player.x * SIZE_ + SIZE_PLYR / 2;
	float Ay = data->player.y * SIZE_ + SIZE_PLYR / 2;
	float dx = Bx - Ax;
	float dy = By - Ay;
	float step;
	float i = 0;
	int pixel;
	int color = 0xff4d4d;
	if (dx >= dy)
		step = fabs(dx);
	else
		step = fabs(dy);
	while (i < step)
	{
		Ax += dx / step;
		Ay += dy / step;
		pixel = ((int)Ay * data->line_length) + ((int)Ax * 4);
		if (pixel > 0)
		{
			data->addr[pixel + 0] = (color) & 0xFF;
			data->addr[pixel + 1] = (color >> 8) & 0xFF;
			data->addr[pixel + 2] = (color >> 16) & 0xFF;
			data->addr[pixel + 3] = (color >> 24);
		}
		i++;
	}
}

void	draw_player(t_data *data, t_ray *ray)
{
	int pixel;
	int color = 0xff0000;
	int i = data->player.x * SIZE_;
	int j = data->player.y * SIZE_;

	while (j < data->player.y * SIZE_ + SIZE_PLYR)
	{
		i = data->player.x * SIZE_;
		while (i < data->player.x * SIZE_ + SIZE_PLYR)
		{
			pixel = (j * data->line_length) + (i * 4);
			data->addr[pixel + 0] = (color) & 0xFF;
			data->addr[pixel + 1] = (color >> 8) & 0xFF;
			data->addr[pixel + 2] = (color >> 16) & 0xFF;
			data->addr[pixel + 3] = (color >> 24);
			i++;
		}
		j++;
	}
	while (ray)
	{
		draw_xray(data, ray->x, ray->y);
		ray = ray->next;
	}
}

void	get_info(t_data *data)
{
	int i = 0;
	int j = 0;

	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i] && data->map[j][i] != '\n')
		{
			// if (data->map[j][i] == '1')
			// 		printf("[%d, %d]\n",i,j);
			if (is_player(data->map[j][i]))
			{
				data->player.x = i;
				data->player.y = j;
				data->player.h_x = data->player.x * SIZE_ + SIZE_PLYR/2;
				data->player.h_y = data->player.y * SIZE_ + SIZE_PLYR/2;
				data->player.v_x = data->player.x * SIZE_ + SIZE_PLYR/2;
				data->player.v_y = data->player.y * SIZE_ + SIZE_PLYR/2;
				if (data->map[j][i] == 'N')
					data->player.rotatedirection = M_PI_2;
				if (data->map[j][i] == 'E')
					data->player.rotatedirection = 0;
				if (data->map[j][i] == 'S')
					data->player.rotatedirection = 3 * M_PI_2;
				if (data->map[j][i] == 'W')
					data->player.rotatedirection = M_PI;
			}
			i++;
		}
		j++;
	}
}