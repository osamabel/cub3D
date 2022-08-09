/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:49:32 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/09 08:51:24 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_ray	*new_ray(int id, float x, float y, float distance, char status)
{
	t_ray	*node;
	float	projection_distance;

	projection_distance = (WIDTH / 2) / tan(ANGLE_VIEW / 2);
	node = (t_ray *)malloc(sizeof(t_ray));
	if (!node)
		return (0);
	node->id = id;
	node->status = status;
	node->x = x;
	node->y = y;
	node->distance = distance;
	node->wallheigth = projection_distance * (SIZE_ / distance );
	node->next = NULL;
	return (node);
}

void	add_ray(t_ray **list, t_ray *ray)
{
	t_ray *last;

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
	else
	{
		//free
		exit(10);
	}
}

void	clear_rays(t_ray **list)
{
	t_ray *node;

	if (list)
	{
		node = *list;
		while (*list)
		{
			node = *list;
			*list = (*list)->next;
			free(node);
		}
		free(list);
	}
}

t_ray	*update_ray(t_data *data)
{
	float	angle;
	t_ray	*ray;
	int		i=0;

	ray = NULL;
	angle = data->player.rotatedirection - ANGLE_VIEW / 2;
	while (angle < data->player.rotatedirection + ANGLE_VIEW / 2)
	{
		data->player.h_x = data->player.x * SIZE_ + SIZE_PLYR / 2;
		data->player.h_y = data->player.y * SIZE_ + SIZE_PLYR / 2;
		data->player.v_x = data->player.x * SIZE_ + SIZE_PLYR / 2;
		data->player.v_y = data->player.y * SIZE_ + SIZE_PLYR / 2;
		horizontal_initial_points(data, angle);
		vertical_initial_points(data, angle);
		horizontal_points(data, angle);
		vertical_points(data, angle);
		if (data->player.v_distance < data->player.h_distance)
			add_ray(&ray, new_ray(i,data->player.v_x, data->player.v_y, data->player.v_distance * cos(data->player.rotatedirection - angle),'V'));
		else
			add_ray(&ray, new_ray(i,data->player.h_x, data->player.h_y, data->player.h_distance * cos(data->player.rotatedirection - angle), 'H'));
		angle += ANGLE_VIEW / WIDTH;
		i++;
	}
	return (ray);
}