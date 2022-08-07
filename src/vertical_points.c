/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:01:56 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/07 14:28:07 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	vertical_initial_points(t_data *data, float angle)
{
	float v_x;
	float v_y;
	float v_dx;
	float v_dy;

	v_x = data->player.v_x;
	v_y = data->player.v_y;
	if (cos(angle) > 0)
		data->player.v_x = SIZE_ * (int)(v_x/SIZE_) + SIZE_;
	else
		data->player.v_x = SIZE_ * (int)(v_x/SIZE_);
	v_dx = data->player.v_x - v_x;
	v_dy = v_dx * tan(angle);
	data->player.v_y = v_y - v_dy;
	data->player.v_distance = hypot(v_dx, v_dy);
}

void	vertical_points(t_data *data, float angle)
{
	float v_dx;
	float v_dy;
	float i = 0;
	v_dx = SIZE_;
	v_dy = SIZE_ * tan(angle);
	if ((sin(angle) > 0 && v_dy > 0) || (sin(angle) < 0 && v_dy < 0))
		v_dy *= -1;
	if (cos(angle) < 0)
	{
		i++;
		v_dx *= -1;
	}
	while (point_in_range(data, (int)((data->player.v_x - i) / SIZE_), (int)(data->player.v_y / SIZE_)))
	{
		if (check_wall_points(data, (int)((data->player.v_x - i) / SIZE_),(int)(data->player.v_y / SIZE_)))
			break ;
		data->player.v_distance += hypot(v_dx, v_dy);
		data->player.v_x += v_dx;
		data->player.v_y += v_dy;
	}
}
