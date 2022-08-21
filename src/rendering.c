/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 08:37:48 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/21 16:24:28 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_sky(t_data *data, int x, int y, int *alpha)
{
	if (y <= (HEIGHT / 2))
	{
		if (HEIGHT / 2 - y < 255)
			(*alpha)++;
		set_point(data, x, y);
		put_pixel(data, data->texture.sky, *alpha);
	}
}

void	draw_floor(t_data *data, int x, int y, int *alpha)
{
	if (y >= (HEIGHT / 2))
	{
		if (y - HEIGHT / 2 < 255)
			(*alpha)--;
		set_point(data, x, y);
		put_pixel(data, data->texture.floor, *alpha);
	}
}

char	*texture_direction(t_data *data, t_ray *ray, int *i)
{
	if (ray->status == 'H')
	{
		if (ray->y < data->player.y * SIZE_ + SIZE_PLYR / 2)
			data->texture.wall_buff = mlx_get_data_addr(data->texture.wall_no, \
			&data->bits_per_pixel, &data->line_length_wall, &data->endian);
		if (ray->y > data->player.y * SIZE_ + SIZE_PLYR / 2)
			data->texture.wall_buff = mlx_get_data_addr(data->texture.wall_so, \
			&data->bits_per_pixel, &data->line_length_wall, &data->endian);
		*i = (fmod(ray->x, SIZE_) * data->texture.wall_w) / SIZE_;
	}
	if (ray->status == 'V')
	{
		if (ray->x < data->player.x * SIZE_ + SIZE_PLYR / 2)
			data->texture.wall_buff = mlx_get_data_addr(data->texture.wall_we, \
			&data->bits_per_pixel, &data->line_length_wall, &data->endian);
		if (ray->x > data->player.x * SIZE_ + SIZE_PLYR / 2)
			data->texture.wall_buff = mlx_get_data_addr(data->texture.wall_ea, \
			&data->bits_per_pixel, &data->line_length_wall, &data->endian);
		*i = (fmod(ray->y, SIZE_) * data->texture.wall_h) / SIZE_;
	}
	return (0);
}

void	draw_wall(t_data *data, t_ray *ray, int x, int y)
{
	int	i;
	int	j;
	int	alpha;

	i = 0;
	if (y > (HEIGHT / 2) - (ray->wallheigth / 2) && y <= (HEIGHT / 2) + \
	(ray->wallheigth / 2))
	{
		alpha = 0;
		alpha = (int)ray->distance + 70;
		if (alpha > 255)
			alpha = 255;
		texture_direction(data, ray, &i);
		j = fmod(y - (HEIGHT / 2 - ray->wallheigth / 2), ray->wallheigth) * \
		data->texture.wall_h / ray->wallheigth;
		set_point(data, x, y);
		put_pixel(data, color_convert(data->texture.wall_buff, \
		data->line_length_wall, i, j), alpha);
	}
}

void	rendring(t_data *data, t_ray *ray)
{
	int	x;
	int	y;
	int	alpha_floor;
	int	alpha_sky;

	y = 0;
	x = 0;
	while (ray && x <= WIDTH)
	{
		y = 0;
		alpha_floor = 255;
		alpha_sky = 0;
		while (y < HEIGHT)
		{
			draw_sky(data, x, y, &alpha_sky);
			draw_floor(data, x, y, &alpha_floor);
			draw_wall(data, ray, x, y);
			y++;
		}
		ray = ray->next;
		x++;
	}
}
