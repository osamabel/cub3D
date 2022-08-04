/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_points.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 09:01:56 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/04 18:55:31 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int check_wall_v_points(t_data *data, float x, float y, float angle)
{
	int i = 0;

	y = (int)(y/SIZE_) * SIZE_;
	if (cos(angle) > 0)
		x = (int)((x + 0.1)/SIZE_) * SIZE_;
	else
		x = (int)((x - 0.1)/SIZE_) * SIZE_;
	while(i < data->info.blocks && !(x == data->info.walls[i].x && y == data->info.walls[i].y))
		i++;
	if (data->map[(int)y / SIZE_][(int)x / SIZE_] == '1')
		return (1);
	return (0);
}

void	vertical_points(t_data *data, float angle)
{
	float v_x,v_y;
	float v_dx,v_dy;
	int i = 0;
	while (data->player.ray.v_y < data->col * SIZE_ && data->player.ray.v_y > 0 && !check_wall_v_points(data, data->player.ray.v_x, data->player.ray.v_y, angle))
	{
		v_x = data->player.ray.v_x;
		v_y = data->player.ray.v_y;
		if (i == 0)
		{
			if (cos(angle) > 0)
				data->player.ray.v_x = SIZE_ * (int)((v_x + 0.001)/SIZE_) + SIZE_;
			else
				data->player.ray.v_x = SIZE_ * (int)((v_x - 0.001)/SIZE_);
			i++;
		}
		else
		{
			if (cos(angle) > 0)
				data->player.ray.v_x += SIZE_;
			else
				data->player.ray.v_x -= SIZE_;
		}
		v_dx = data->player.ray.v_x - v_x;
		v_dy = v_dx * tan(angle);
		data->player.ray.v_y = v_y - v_dy;
		data->player.ray.v_dx += v_dx;
		data->player.ray.v_dy += v_dy;
	}
	// int i = 0,j = 0;
	// data->ray_v = mlx_xpm_file_to_image(data->mlx, "images/red.xpm", &data->x, &data->y);
	// while (j < 5)
	// {
	// 	i = 0;
	// 	while (i < 5)
	// 	{
	// 		mlx_put_image_to_window(data->mlx, data->wind, data->ray_v, data->player.ray.v_x + i, data->player.ray.v_y + j);
	// 		i++;
	// 	}
	// 	j++;
	// }
	data->player.ray.v_distance = sqrt(pow(data->player.ray.v_dx, 2) + pow(data->player.ray.v_dy, 2));
	data->player.ray.v_dx = 0;
	data->player.ray.v_dy = 0;
}

