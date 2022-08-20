/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:02:44 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/19 16:11:49 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void gun_idle(t_data *data)
{
	static int frame;

	if (frame < 3)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/idle/idle1.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 6)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/idle/idle2.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 9)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/idle/idle3.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 12)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/idle/idle4.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 15)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/idle/idle5.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 18)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/idle/idle6.xpm",&data->texture.gun_w, &data->texture.gun_h);
	if(frame == 18)
		frame = 0;
	frame++;
}

void gun_shoot(t_data *data)
{
	static int frame;

	if (frame < 1)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/shoot/shoot1.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 2)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/shoot/shoot2.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 3)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/shoot/shoot3.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 4)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/shoot/shoot5.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 5)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/shoot/shoot6.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 6)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/shoot/shoot7.xpm",&data->texture.gun_w, &data->texture.gun_h);
	else if (frame < 7)
		data->texture.gun = mlx_xpm_file_to_image(data->mlx, "images/gun/shoot/shoot8.xpm",&data->texture.gun_w, &data->texture.gun_h);
	if(frame == 8)
	{
		data->player.shoot = 0;
		frame = 0;
	}
	frame++;
}

void draw_sprite(t_data *data, int x, int y)
{
	int i;
	int j;
	int pixel;
	int pixel_gun;

	i = 0;
	j = 0;
	while (i < data->texture.gun_w)
	{
		j = 0;
		while (j < data->texture.gun_h)
		{
			pixel = (y + j) * data->line_length + (x + i) * data->bits_per_pixel/8;
			pixel_gun = j * data->texture.gun_size + i * data->bits_per_pixel/8;
			if (!(data->texture.gun_buff[pixel_gun + 0] == 0 && data->texture.gun_buff[pixel_gun + 1] == 0 && data->texture.gun_buff[pixel_gun + 2] == 0))
			{
				data->addr[pixel + 0] = data->texture.gun_buff[pixel_gun + 0];
				data->addr[pixel + 1] = data->texture.gun_buff[pixel_gun + 1];
				data->addr[pixel + 2] = data->texture.gun_buff[pixel_gun + 2];
				data->addr[pixel + 3] = 0;
			}
			j++;
		}
		i++;
	}
}

void sprite_gun(t_data *data)
{

	if (data->player.shoot)
		gun_shoot(data);
	else
		gun_idle(data);
	data->texture.gun_buff = mlx_get_data_addr(data->texture.gun, &data->bits_per_pixel, &data->texture.gun_size, &data->endian);
	draw_sprite(data, WIDTH - data->texture.gun_w, HEIGHT - data->texture.gun_h);
}
