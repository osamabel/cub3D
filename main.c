/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:55:04 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/08 08:09:40 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int keyprelease(int keycode, void *parm)
{
	t_data *data;
	data = (t_data *)parm;
	if (keycode == 124) // >
		data->player.turndirection = 0;
	if (keycode == 123) // <
		data->player.turndirection = 0;
	if (keycode == 13) // ^
		data->player.walkdirection = 0;
	if (keycode == 1) // v
		data->player.walkdirection = 0;
	if (keycode == 0) // a
		data->player.sidedirection = 0;
	if (keycode == 2) // d
		data->player.sidedirection = 0;
	return 0;
}

int keypress(int keycode, void *parm)
{
	t_data *data;

	data = (t_data *)parm;
	if (keycode == 124) // (>
		data->player.turndirection = -1;
	if (keycode == 123) // <)
		data->player.turndirection = 1;
	if (keycode == 13) // ^ W
		data->player.walkdirection = 1;
	if (keycode == 1) // v S
		data->player.walkdirection = -1;
	if (keycode == 0) //  A
		data->player.sidedirection = 1;
	if (keycode == 2) //  D
		data->player.sidedirection = -1;
	return 0;
}

t_ray	*new_ray(int id, float x, float y, float distance, char status)
{
	t_ray	*node;
	float	projection_distance;

	projection_distance = (WIDTH / 2) / tan(ANGLE_VIEW / 2);
	node = (t_ray *)malloc(sizeof(t_ray));
	if (!node)
		exit (1);
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

	if (list && ray)
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

void draw_wall(t_data *data, t_ray *ray)
{
	int pixel;
	int color;
	int x = WIDTH;
	int y = 0;
	while (x > 0)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y <= (HEIGHT / 2) - (ray->wallheigth / 2))
				color = 0xffffff;
			else if (y >= (HEIGHT / 2) + (ray->wallheigth / 2))
				color = 0x000000;
			else
			{
				if (ray->status == 'H')
					color = 0xd9d9d9;
				if (ray->status == 'V')
					color = 0xbfbfbf;
			}
			pixel = (y * data->line_length) + (x * 4);
			if (pixel > 0)
			{
				data->addr[pixel + 0] = (color) & 0xFF;
				data->addr[pixel + 1] = (color >> 8) & 0xFF;
				data->addr[pixel + 2] = (color >> 16) & 0xFF;
				data->addr[pixel + 3] = (color >> 24);
			}
			y++;
		}
		ray = ray->next;
		x--;
	}
}

int draw(t_data *data)
{
	t_ray	*ray;
	if (data->player.sidedirection)
	{
		data->player.x += cos(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
		data->player.y += -sin(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
	}
	if (data->player.walkdirection)
	{
		data->player.x += cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
		data->player.y += -sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	}
	if (data->player.turndirection)
		data->player.rotatedirection += data->player.turndirection * data->player.rotatespeed;
	mlx_clear_window(data->mlx, data->wind);
	ray = update_ray(data);
	draw_wall(data, ray);
	draw_background(data);
	draw_player(data, ray);
	mlx_put_image_to_window(data->mlx, data->wind, data->img, 0, 0);
	return (0);
}

int main(void)
{
	t_data data;
	initial(&data);
	get_info(&data);
	mlx_loop_hook(data.mlx, draw, &data);
	mlx_hook(data.wind, 3, 0, keyprelease, &data);
	mlx_hook(data.wind, 2, 0, keypress, &data);
	mlx_loop(data.mlx);
}




	// for(int y = 0;y < data.row;y++)
	// {
	// 	for(int x = 0;x < data.col;x++)
	// 	{
	// 		printf("[%c]",data.map[y][x]);
	// 	}
	// 	printf("\n");
	// }