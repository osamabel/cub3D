/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:37:48 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/09 09:19:33 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// mlx_get_data_addr

void draw_wall(t_data *data, t_ray *ray)
{
	int color;
	int sky = data->texture.C;
	int floor = data->texture.F;
	int x = WIDTH;
	int y = 0;
	int z = 255;
 	int alpha = 0;
	while (x > 0)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y <= (HEIGHT / 2))
			{
				if (y > 254)
					put_pixel(data, sky, x, y, 255);
				else
					put_pixel(data, sky, x, y, y);
			}
			if (y >= (HEIGHT / 2))
			{
				if (z < 1)
					put_pixel(data, floor, x, y, 0);
				else
					put_pixel(data, floor, x, y, z);
				z--;
			}
			if (y > (HEIGHT / 2) - (ray->wallheigth / 2) && y < (HEIGHT / 2) + (ray->wallheigth / 2))
			{
				if (ray->status == 'H')
					color = 0xffa366;
				if (ray->status == 'V')
					color = 0xfcbf82;
				alpha = (int)ray->distance + 70;
				if (alpha > 255)
					alpha = 255;
				put_pixel(data, color, x, y, alpha);
			}
			alpha = 0;
			y++;
		}
		z = 255;
		ray = ray->next;
		x--;
	}
}