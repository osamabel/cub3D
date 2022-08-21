/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:02:44 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/21 16:26:11 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	gun_idle(t_data *data)
{
	static int	frame;
	char		*path;

	path = 0;
	if (frame < 2)
		path = "images/gun/idle/idle1.xpm";
	else if (frame < 4)
		path = "images/gun/idle/idle2.xpm";
	else if (frame < 6)
		path = "images/gun/idle/idle3.xpm";
	else if (frame < 8)
		path = "images/gun/idle/idle4.xpm";
	else if (frame < 10)
		path = "images/gun/idle/idle5.xpm";
	else if (frame < 12)
		path = "images/gun/idle/idle6.xpm";
	if (frame == 12)
	{
		path = "images/gun/idle/idle1.xpm";
		frame = 0;
	}
	data->texture.gun = mlx_xpm_file_to_image(data->mlx, path, \
	&data->texture.gun_w, &data->texture.gun_h);
	frame++;
}

void	gun_shoot(t_data *data)
{
	static int	frame;
	char		*path;

	path = 0;
	if (frame < 1)
		path = "images/gun/shoot/shoot1.xpm";
	else if (frame < 2)
		path = "images/gun/shoot/shoot2.xpm";
	else if (frame < 3)
		path = "images/gun/shoot/shoot3.xpm";
	else if (frame < 4)
		path = "images/gun/shoot/shoot4.xpm";
	else if (frame < 5)
		path = "images/gun/shoot/shoot5.xpm";
	else if (frame < 6)
		path = "images/gun/shoot/shoot6.xpm";
	if (frame == 6)
	{
		path = "images/gun/shoot/shoot7.xpm";
		data->player.shoot = 0;
		frame = 0;
	}
	data->texture.gun = mlx_xpm_file_to_image(data->mlx, path, \
	&data->texture.gun_w, &data->texture.gun_h);
	frame++;
}

void	draw_sprite(t_data *data, int x, int y)
{
	int	i;
	int	j;
	int	pix;

	i = 0;
	while (i < data->texture.gun_w)
	{
		j = 0;
		while (j < data->texture.gun_h)
		{
			pix = (j * data->texture.gun_size) + (i * data->bits_per_pixel / 8);
			set_point(data, x + i, y + j);
			if (!is_transparent(data, pix))
				put_pixel(data, color_convert(data->texture.gun_buff, \
				data->texture.gun_size, i, j), 0);
			j++;
		}
		i++;
	}
}

void	sprite_gun(t_data *data)
{
	if (data->player.shoot)
		gun_shoot(data);
	else
		gun_idle(data);
	data->texture.gun_buff = mlx_get_data_addr(data->texture.gun, \
	&data->bits_per_pixel, &data->texture.gun_size, &data->endian);
	draw_sprite(data, WIDTH - data->texture.gun_w, HEIGHT - \
	data->texture.gun_h);
}
