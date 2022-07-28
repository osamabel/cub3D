/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:55:04 by obelkhad          #+#    #+#             */
/*   Updated: 2022/07/28 23:19:18 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
int keyprelease(int keycode, void *parm)
{
	t_data *data;
	data = (t_data *)parm;
	if (keycode == 126) // ^
		data->player.walkdirection = 0;
	if (keycode == 124) // >
		data->player.turndirection = 0;
	if (keycode == 123) // <
		data->player.walkdirection = 0;
	if (keycode == 125) // v
		data->player.turndirection = 0;
	return 0;
}

int keypress(int keycode, void *parm)
{
	t_data *data;
	data = (t_data *)parm;
	re_background(data);

	if (keycode == 126) // ^
	{
		data->player.walkdirection = -1;
		data->player.x += -cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
		data->player.y += sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	}
	else if (keycode == 125) // v
	{
		data->player.walkdirection = 1;
		data->player.x += -cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
		data->player.y += sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	}
	else if (keycode == 124) // >
	{
		data->player.turndirection = -1;
		data->player.rotatedirection += data->player.turndirection * data->player.rotatespeed;
	}
	else if (keycode == 123) // <
	{
		data->player.turndirection = 1;
		data->player.rotatedirection += data->player.turndirection * data->player.rotatespeed;
	}
	printf("[%f]\n",data->player.rotatedirection);
	update(data);
	return 0;
}



void	update(t_data *data)
{
	data->img = mlx_xpm_file_to_image(data->mlx, "images/person.xpm", &data->x, &data->y);
	mlx_put_image_to_window(data->mlx, data->wind, data->img, data->player.x * SIZE_, data->player.y * SIZE_);
}

void	re_background(t_data *data)
{
	int i = 0;
	int j = 0;

	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
				mlx_put_image_to_window(data->mlx, data->wind, data->map_gb, i * SIZE_, j * SIZE_);
			else
				mlx_put_image_to_window(data->mlx, data->wind, data->map_wall, i * SIZE_, j * SIZE_);
			i++;
		}
		j++;
	}
}

void	background(t_data *data)
{
	int i = 0;
	int j = 0;
	static int b;

	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
			{
				data->map_gb = mlx_xpm_file_to_image(data->mlx, "images/444.xpm", &data->x, &data->x);
				mlx_put_image_to_window(data->mlx, data->wind, data->map_gb, i * SIZE_, j * SIZE_);
			}
			else
			{
				data->map_wall = mlx_xpm_file_to_image(data->mlx, "images/fff.xpm", &data->x, &data->y);
				mlx_put_image_to_window(data->mlx, data->wind, data->map_wall, i * SIZE_, j * SIZE_);
			}
			if (is_player(data->map[j][i]) && !b)
			{
				data->player.x = i;
				data->player.y = j;
				if (data->map[j][i] == 'N')
					data->player.rotatedirection = M_PI_2;
				if (data->map[j][i] == 'E')
					data->player.rotatedirection = 0;
				if (data->map[j][i] == 'S')
					data->player.rotatedirection = 3 * M_PI_2;
				if (data->map[j][i] == 'W')
					data->player.rotatedirection = M_PI;
				data->img = mlx_xpm_file_to_image(data->mlx, "images/person.xpm", &data->x, &data->y);
				mlx_put_image_to_window(data->mlx, data->wind, data->img, i * SIZE_, j * SIZE_);
				b = 1;
			}
			i++;
		}
		j++;
	}
}


void	draw_map(t_data *data)
{
	background(data);
}

int main(void)
{
	t_data data;

	initial(&data);
	draw_map(&data);
	mlx_hook(data.wind, 2, 0, keypress, &data);
	mlx_hook(data.wind, 3, 0, keyprelease, &data);
	mlx_loop(data.mlx);
}