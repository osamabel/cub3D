/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:55:04 by obelkhad          #+#    #+#             */
/*   Updated: 2022/07/28 11:33:34 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int keypress(int keycode, void *parm)
{
	t_data *data;
	data = (t_data *)parm;
	printf("> %d\n",keycode);
	// if (keycode == 126) // ^
	// 	data->player.walkdirection += 1;
	// if (keycode == 124) // >
	// 	data->player.turndirection += 1;
	// if (keycode == 123) // <
	// 	data->player.walkdirection -= 1;
	// if (keycode == 125) // v
	// 	data->player.turndirection -= 1;
	// // re_draw(data);
	// update_draw(data);
	// data->player.x = cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	// data->player.y = sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	// put_player(data);
	return 0;
}

void	d_background(t_data *data)
{
	int i = 0;
	int j = 0;

	while (j < data->row * SIZE_)
	{
		i = 0;
		while (i < data->col * SIZE_)
		{
			my_mlx_pixel_put(data, j, i, 0x414141);
			i++;
		}
		j++;
	}
}

void	block(t_data *data)
{
	int i = 0;
	int j = 0;
	while (j <= SIZE_)
	{
		i = 0;
		while (i <= SIZE_)
		{
			my_mlx_pixel_put(data, j, i, 0xffffff);
			i++;
		}
		j++;
	}
}

void	circle(t_data *data)
{
	int i = 0;
	int j = 0;
	int a = SIZE_/2;
	int b = SIZE_/2;
	while (j <= SIZE_ + 5)
	{
		i = 0;
		while (i <= SIZE_)
		{
			if (pow(i-a,2) + pow(j-b,2) < pow(data->player.radius,2))
				my_mlx_pixel_put(data, j, i, 0xff944d);
			else
				my_mlx_pixel_put(data, j, i, 0x0000ff);
			i++;
		}
		j++;
	}
}

void	d_wall(t_data *data)
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
				block(data);
				mlx_put_image_to_window(data->mlx, data->wind, data->img, i * SIZE_, j * SIZE_);
			}
			if (is_player(data->map[j][i]) && !b)
			{
				data->player.x = i;
				data->player.y = j;
				b = 1;
			}
			i++;
		}
		j++;
	}
}

void d_player(t_data *data)
{
	int i = 0;
	int j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (i == data->player.x && j == data->player.y)
			{
				circle(data);
				mlx_put_image_to_window(data->mlx, data->wind, data->img, i * SIZE_ + 10, j * SIZE_+ 20);
			}
			if (data->map[j][i] == '1')
			{
				block(data);
				mlx_put_image_to_window(data->mlx, data->wind, data->img, i * SIZE_, j * SIZE_);
			}
			i++;
		}
		j++;
	}
}

void	draw_map(t_data *data)
{
	d_background(data);
	mlx_put_image_to_window(data->mlx, data->wind, data->img, 0, 0);
	d_wall(data);
	d_player(data);

}

int main(void)
{
	t_data data;

	initial(&data);

	draw_map(&data);
	printf("x = %d\n",data.player.x);
	printf("y = %d\n",data.player.y);
	mlx_hook(data.wind, 2, 0, keypress, &data);
	mlx_loop(data.mlx);
}