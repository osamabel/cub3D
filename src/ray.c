/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:49:32 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/21 18:29:54 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_ray	*new_ray(float x, float y, float distance, char status)
{
	t_ray	*node;
	float	projection_distance;

	projection_distance = (WIDTH / 2) / tan((M_PI / 3) / 2);
	node = (t_ray *)malloc(sizeof(t_ray));
	if (!node)
		return (0);
	node->status = status;
	node->x = x;
	node->y = y;
	node->distance = distance;
	node->wallheigth = projection_distance * (SIZE_ / distance);
	node->next = NULL;
	return (node);
}

void	add_ray(t_ray **list, t_ray *ray)
{
	t_ray	*last;

	if (ray)
	{
		if (!(*list))
			*list = ray;
		else
		{
			last = *list;
			while (last->next)
				last = last->next;
			last->next = ray;
		}
	}
}

void	find_wall(t_data *data, float angle)
{
	data->player.h_x = data->player.x * SIZE_ + SIZE_PLYR / 2;
	data->player.h_y = data->player.y * SIZE_ + SIZE_PLYR / 2;
	data->player.v_x = data->player.x * SIZE_ + SIZE_PLYR / 2;
	data->player.v_y = data->player.y * SIZE_ + SIZE_PLYR / 2;
	horizontal_initial_points(data, angle);
	vertical_initial_points(data, angle);
	horizontal_points(data, angle);
	vertical_points(data, angle);
}

t_ray	*update_ray(t_data *data)
{
	float	angle;
	float	fish;
	t_ray	*ray;

	ray = NULL;
	angle = data->player.rotatedirection + (M_PI / 3) / 2;
	while (angle > data->player.rotatedirection - (M_PI / 3) / 2)
	{
		find_wall(data, angle);
		fish = cos(data->player.rotatedirection - angle);
		if (data->player.v_distance < data->player.h_distance)
		{
			data->mid_ray_d = data->player.v_distance * fish;
			add_ray(&ray, new_ray(data->player.v_x, data->player.v_y, \
			data->mid_ray_d, 'V'));
		}
		else
		{
			data->mid_ray_d = data->player.h_distance * fish;
			add_ray(&ray, new_ray(data->player.h_x, data->player.h_y, \
			data->mid_ray_d, 'H'));
		}
		angle -= (M_PI / 3) / (WIDTH);
	}
	return (ray);
}
