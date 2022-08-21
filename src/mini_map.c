/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:26:37 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/21 16:28:25 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_ray(t_data *data, float bx, float by)
{
	float	ax;
	float	ay;
	float	dx;
	float	dy;
	float	step;

	ax = data->player.x * SIZE_ + SIZE_PLYR / 2;
	ay = data->player.y * SIZE_ + SIZE_PLYR / 2;
	dx = bx - ax;
	dy = by - ay;
	if (fabsf(dx) >= fabsf(dy))
		step = fabsf(dx);
	else
		step = fabsf(dy);
	dx = dx / step;
	dy = dy / step;
	while (step-- > 0)
	{
		set_point(data, ax, ay);
		put_pixel(data, 0xff9933, 0);
		ax += dx;
		ay += dy;
	}
}

void	draw_player(t_data *data, t_ray *ray, int x, int y)
{
	int		i;
	int		j;
	t_ray	*head;

	i = x;
	j = y;
	while (j < y + SIZE_PLYR)
	{
		i = x;
		while (i < x + SIZE_PLYR)
		{
			set_point(data, i++, j);
			put_pixel(data, 0xff9933, 0);
		}
		j++;
	}
	while (ray)
	{
		head = ray;
		draw_ray(data, ray->x, ray->y);
		ray = ray->next;
		free(head);
	}
}

void	draw_mini_map(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;

	j = 0;
	y = -1;
	while (++y < data->row * SIZE_)
	{
		x = -1;
		i = 0;
		while (++x < (int)ft_strlen(data->map[j]) * SIZE_)
		{
			set_point(data, x, y);
			if (data->map[j][i] == '1')
				put_pixel(data, 0x282828, 0);
			else if (data->map[j][i] == '0' || is_player((data->map[j][i])))
				put_pixel(data, 0xCCCCCC, 0);
			if ((x + 1) % SIZE_ == 0)
				i++;
		}
		if ((y + 1) % SIZE_ == 0)
			j++;
	}
}

void	mini_map(t_data *data, t_ray *ray)
{
	draw_mini_map(data);
	draw_player(data, ray, data->player.x * SIZE_, data->player.y * SIZE_);
}
