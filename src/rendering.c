/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:37:48 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/20 16:58:42 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_sky(t_data *data, int x, int y, int color, int *alpha)
{
	if (y <= (HEIGHT / 2))
	{
		if (HEIGHT / 2 - y < 255)
			(*alpha)++;
		put_pixel(data, data->addr, color, x, y, *alpha);
	}
}

void	draw_floor(t_data *data, int x, int y, int color, int *alpha)
{
	if (y >= (HEIGHT / 2))
	{
		if (y - HEIGHT / 2 < 255)
			(*alpha)--;
		put_pixel(data, data->addr, color, x, y, *alpha);
	}
}

void draw_wall(t_data *data, t_ray *ray, int x, int y, int *alpha)
{
	int i;
	int j;
	int pixel_wall;
	int pixel;
i = 0;
	if (y > (HEIGHT / 2) - (ray->wallheigth / 2) && y <= (HEIGHT / 2) + (ray->wallheigth / 2))
	{
		*alpha = 0;
		*alpha = (int)ray->distance + 70;
		if (*alpha > 255)
			*alpha = 255;

		data->texture.wall_buff = mlx_get_data_addr(data->texture.wall_EA, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
		if (ray->status == 'H')
		{
			if (ray->y < data->player.y * SIZE_ + SIZE_PLYR / 2)
				data->texture.wall_buff = mlx_get_data_addr(data->texture.wall_NO, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
			if (ray->y > data->player.y * SIZE_ + SIZE_PLYR / 2)
				data->texture.wall_buff = mlx_get_data_addr(data->texture.wall_SO, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
			i = (fmod(ray->x, SIZE_) * data->texture.no_w) / SIZE_;
		}
		if (ray->status == 'V')
		{
			if (ray->x < data->player.x * SIZE_ + SIZE_PLYR / 2)
				data->texture.wall_buff = mlx_get_data_addr(data->texture.wall_WE, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
			if (ray->x > data->player.x * SIZE_ + SIZE_PLYR / 2)
				data->texture.wall_buff = mlx_get_data_addr(data->texture.wall_EA, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
			i = (fmod(ray->y, SIZE_) * data->texture.no_h) / SIZE_;
		}

		pixel = y * data->line_length + x * data->bits_per_pixel/8;
		j = fmod(y - (HEIGHT / 2 - ray->wallheigth / 2), ray->wallheigth) * data->texture.no_h / ray->wallheigth;
		pixel_wall = j * data->line_length_wall + i * data->bits_per_pixel/8;
		if (pixel > 0 && pixel_wall > 0 && j < data->texture.no_h)
		{
			data->addr[pixel + 0] = data->texture.wall_buff[pixel_wall + 0];
			data->addr[pixel + 1] = data->texture.wall_buff[pixel_wall + 1];
			data->addr[pixel + 2] = data->texture.wall_buff[pixel_wall + 2];
			data->addr[pixel + 3] = *alpha;
		}
	}
}

void rendring(t_data *data, t_ray *ray)
{
	int x;
	int y;
	int alpha_floor;
	int alpha_sky;
 	int alpha_wall;

	y = 0;
	x = WIDTH;
	while (ray && x >= 0)
	{
		y = 0;
		alpha_floor = 255;
		alpha_sky = 0;
		while (y < HEIGHT)
		{
			draw_sky(data, x, y, data->texture.C, &alpha_sky);
			draw_floor(data, x, y, data->texture.F, &alpha_floor);
			draw_wall(data, ray, x, y, &alpha_wall);
			y++;
		}
		ray = ray->next;
		x--;
	}
}
