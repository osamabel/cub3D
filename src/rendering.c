/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:37:48 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/10 21:02:31 by obelkhad         ###   ########.fr       */
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
			i = ((int)ray->x % SIZE_ * data->x) / SIZE_;
		if (ray->status == 'V')
			i = ((int)ray->y % SIZE_ * data->x) / SIZE_;
			point = y - ((HEIGHT / 2) - (ray->wallheigth / 2));
			j = (point % (int)ray->wallheigth  * data->x) / (int)ray->wallheigth;
			pixel_wall = (j * data->line_length_wall) + (i * data->bits_per_pixel/8);
			pixel = (y * data->line_length) + (x * data->bits_per_pixel/8);
			if (pixel > 0 && pixel_wall > 0 && j < data->x)
			{
				char c0 = data->wall[pixel_wall + 0];
				char c1 = data->wall[pixel_wall + 1];
				char c2 = data->wall[pixel_wall + 2];
				data->addr[pixel + 0] = c0;
				data->addr[pixel + 1] = c1;
				data->addr[pixel + 2] = c2;
				data->addr[pixel + 3] = *alpha;
			}
		// }
		// else
		// 	put_pixel(data, data->addr, 0xfedccc, x, y, *alpha);
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

// void draw_wall_texture(t_data *data, t_ray *ray)
// {
// 	int color;
// 	int sky = data->texture.C;
// 	int floor = data->texture.F;
// 	int x = WIDTH;
// 	int y = 0;
// 	int z = 255;
//  	int alpha = 0;
// 	while (ray && x >= 0)
// 	{
// 		y = 0;
// 		while (y <= HEIGHT)
// 		{
// 			draw_sky(data, x, y, sky);
// 			draw_floor(data, x, y, sky);
// 			if (y >= (HEIGHT / 2))
// 			{
// 				if (z < 1)
// 					put_pixel(data, floor, x, y, 0);
// 				else
// 					put_pixel(data, floor, x, y, z);
// 				z--;
// 			}
// 			if (y > (HEIGHT / 2) - (ray->wallheigth / 2) && y < (HEIGHT / 2) + (ray->wallheigth / 2))
// 			{
// 				if (ray->status == 'H')
// 					color = 0xffa366;
// 				if (ray->status == 'V')
// 					color = 0xfcbf82;
// 				alpha = (int)ray->distance + 70;
// 				if (alpha > 255)
// 					alpha = 255;
// 				put_pixel(data, color, x, y, alpha);
// 			}
// 			alpha = 0;
// 			y++;
// 		}
// 		z = 255;
// 		ray = ray->next;
// 		x--;
// 	}
// }