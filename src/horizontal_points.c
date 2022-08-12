/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_points.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:58:34 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/12 14:53:53 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	horizontal_initial_points(t_data *data, float angle)
{
	float h_x;
	float h_y;
	float h_dx;
	float h_dy;

	h_x = data->player.h_x;
	h_y = data->player.h_y;
	if (sin(angle) > 0)
		data->player.h_y = SIZE_ * (int)(h_y/SIZE_);
	else
		data->player.h_y = SIZE_ * (int)(h_y/SIZE_) + SIZE_;
	h_dy = h_y - data->player.h_y;
	h_dx = h_dy / tan(angle);
	data->player.h_x = h_x + h_dx;
	data->player.h_distance = hypot(h_dx, h_dy);
}

void	horizontal_points(t_data *data, float angle)
{
	float h_dx;
	float h_dy;
	float i = 0;

	h_dx = SIZE_ / tan(angle);
	h_dy = SIZE_;
	if ((cos(angle) > 0 && h_dx < 0) || (cos(angle) < 0 && h_dx > 0))
		h_dx *= -1;
	if (sin(angle) > 0)
	{
		i++;
		h_dy *= -1;
	}
	while (point_in_range(data, (int)(data->player.h_x / SIZE_), (int)((data->player.h_y - i) / SIZE_)))
	{
		if (is_wall(data, (int)(data->player.h_x / SIZE_),(int)((data->player.h_y - i) / SIZE_)))
			break ;
		data->player.h_distance += hypot(h_dx, h_dy);
		data->player.h_x += h_dx;
		data->player.h_y += h_dy;
	}
}
