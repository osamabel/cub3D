/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:37:48 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/12 17:04:40 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_sky(t_data *data, int x, int y, int color)
{
	if (y <= (HEIGHT / 2))
	{
		if (y > 254)
			put_pixel(data, data->addr, color, x, y, 255);
		else
			put_pixel(data, data->addr, color, x, y, y);
	}
}

void	draw_floor(t_data *data, int x, int y, int color, int *alpha)
{
	if (y >= (HEIGHT / 2))
	{
		if (*alpha < 1)
			put_pixel(data, data->addr, color, x, y, 0);
		else
			put_pixel(data, data->addr, color, x, y, *alpha);
		(*alpha)--;
	}
}

void draw_wall(t_data *data, t_ray *ray, int x, int y, int *alpha)
{
	int i;
	int j;
	int pixel_wall;
	int pixel;
	int point;

	if (y > (HEIGHT / 2) - (ray->wallheigth / 2) && y <= (HEIGHT / 2) + (ray->wallheigth / 2))
	{
		*alpha = 0;
		*alpha = (int)ray->distance + SHADING;
		if (*alpha > 250)
			*alpha = 250;

		if (ray->status == 'H')
		{
			i = ((int)ray->x % SIZE_ * data->wall_w) / SIZE_;
			if (sin(data->player.rotatedirection) > 0)
				data->wall_buff = mlx_get_data_addr(data->wall_N, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
			else
				data->wall_buff = mlx_get_data_addr(data->wall_S, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
		}
		if (ray->status == 'V')
		{
			i = ((int)ray->y % SIZE_ * data->wall_h) / SIZE_;
			if (cos(data->player.rotatedirection) > 0)
				data->wall_buff = mlx_get_data_addr(data->wall_E, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
			else
				data->wall_buff = mlx_get_data_addr(data->wall_W, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
		}

		point = y - ((HEIGHT / 2) - (ray->wallheigth / 2));
		pixel = (y * data->line_length) + (x * data->bits_per_pixel/8);
		j = (point % (int)ray->wallheigth  * data->wall_h) / (int)ray->wallheigth;
		pixel_wall = (j * data->line_length_wall) + (i * data->bits_per_pixel/8);
		if (pixel > 0 && pixel_wall > 0 && j < data->wall_h)
		{
			data->addr[pixel + 0] = data->wall_buff[pixel_wall + 0];
			data->addr[pixel + 1] = data->wall_buff[pixel_wall + 1];
			data->addr[pixel + 2] = data->wall_buff[pixel_wall + 2];
			data->addr[pixel + 3] = *alpha;
		}
	}
}

void rendring(t_data *data, t_ray *ray)
{
	int x;
	int y;
	int alpha_floor;
 	int alpha_wall;

	y = 0;
	x = WIDTH;
	while (ray && x >= 0)
	{
		y = 0;
		alpha_floor = 255;
		while (y <= HEIGHT)
		{
			draw_sky(data, x, y, data->texture.C);
			draw_floor(data, x, y, data->texture.F, &alpha_floor);
			draw_wall(data, ray, x, y, &alpha_wall);
			y++;
		}
		ray = ray->next;
		x--;
	}
}
