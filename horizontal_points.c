/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_points.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 08:58:34 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/04 20:27:39 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int check_wall_h_points(t_data *data, float x, float y, float angle)
{
	int i = 0;

	x = (int)(x/SIZE_) * SIZE_;
	if (sin(angle) > 0)
		y = (int)((y - 0.1)/SIZE_) * SIZE_;
	else
		y = (int)((y + 0.1)/SIZE_) * SIZE_;
	while(i < data->info.blocks && !(x == data->info.walls[i].x && y == data->info.walls[i].y))
		i++;
	if (data->map[(int)y / SIZE_][(int)x / SIZE_] == '1')
		return (1);
	return (0);
}


void	horizontal_points(t_data *data, float angle)
{
	float h_x,h_y;
	float h_dx,h_dy;
	int i = 0;
	while (data->player.ray.h_x < data->row * SIZE_ && data->player.ray.h_x > 0 && !check_wall_h_points(data, data->player.ray.h_x, data->player.ray.h_y, angle))
	{
		h_x = data->player.ray.h_x;
		h_y = data->player.ray.h_y;
		if (i == 0)
		{
			if (sin(angle) > 0)
				data->player.ray.h_y = SIZE_ * (int)(h_y/SIZE_);
			else
				data->player.ray.h_y = SIZE_ * (int)(h_y/SIZE_) + SIZE_;
			i++;
		}
		else
		{
			if (sin(angle) > 0)
				data->player.ray.h_y -= SIZE_;
			else
				data->player.ray.h_y += SIZE_;
		}
		h_dy = h_y - data->player.ray.h_y;
		h_dx = h_dy / tan(angle);
		data->player.ray.h_x = h_x + h_dx;
		data->player.ray.h_dx += h_dx;
		data->player.ray.h_dy += h_dy;
	}


// i = 0;
// 	int j = 0;
// 	data->ray_h = mlx_xpm_file_to_image(data->mlx, "images/blue.xpm", &data->x, &data->y);
// 	while (j < 5)
// 	{
// 		i = 0;
// 		while (i < 5)
// 		{
// 			mlx_put_image_to_window(data->mlx, data->wind, data->ray_h, data->player.ray.h_x + i, data->player.ray.h_y + j);
// 			i++;
// 		}
// 		j++;
// 	}
	data->player.ray.h_distance = sqrt(pow(data->player.ray.h_dx, 2) + pow(data->player.ray.h_dy, 2));
	data->player.ray.h_dx = 0;
	data->player.ray.h_dy = 0;
}


