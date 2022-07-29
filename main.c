/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:55:04 by obelkhad          #+#    #+#             */
/*   Updated: 2022/07/29 20:12:02 by obelkhad         ###   ########.fr       */
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
	if (keycode == 13) // ^
		data->player.walkdirection = 1;
	if (keycode == 1) // v
		data->player.walkdirection = -1;
	if (keycode == 0) // >
		data->player.sidedirection = 1;
	if (keycode == 2) // <
		data->player.sidedirection = -1;
	data->player.key = keycode;
	return 0;
}

int	is_wall_front_player(t_data *data, int var)
{
	int i = 0;
	float next_x, next_y;
	int bloc_x, bloc_y;
	if (var)
	{
		printf("var\n");
		next_x = (data->player.x + cos(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection) * SIZE_;
		next_y = (data->player.y + -sin(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection) * SIZE_;
	}
	else
	{
		next_x = (data->player.x + cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection) * SIZE_;
		next_y = (data->player.y + -sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection) * SIZE_;
	}
	printf("x = %f, y = %f\n",next_x,next_y);
	if (data->player.key == 13 || data->player.key == 0)
	{
		bloc_x = SIZE_ * (int)(next_x/SIZE_);
		bloc_y = SIZE_ * (int)(next_y/SIZE_) ;
	}
	if (data->player.key == 1 || data->player.key == 2)
	{
		bloc_x = SIZE_ * (int)(next_x/SIZE_) + SIZE_;
		bloc_y = SIZE_ * (int)(next_y/SIZE_) + SIZE_;
	}
	printf("Bx = %d, By = %d\n\n",bloc_x,bloc_y);
	while (i < data->info.blocks)
	{
		if (data->info.walls[i].x == bloc_x && data->info.walls[i].y == bloc_y)
			break;
		i++;
	}
	printf("Bx = %d,",i);
	if (i == data->info.blocks)
		return (1);
	return (0);
}


void	update_player(t_data *data)
{
	if (data->player.sidedirection && is_wall_front_player(data, 1))
	{
		data->player.x += cos(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
		data->player.y += -sin(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
	}
	if (data->player.walkdirection && is_wall_front_player(data, 0))
	{
		data->player.x += cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
		data->player.y += -sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	}
	if (data->player.turndirection)
		data->player.rotatedirection += data->player.turndirection * data->player.rotatespeed;
	// printf("[%f, %f]\n",data->player.x, data->player.y);
	data->img = mlx_xpm_file_to_image(data->mlx, "images/person_1.xpm", &data->x, &data->y);
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


int draw(t_data *data)
{
	re_background(data);
	update_player(data);
	return (0);
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
				data->info.blocks++;
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
				data->img = mlx_xpm_file_to_image(data->mlx, "images/person_1.xpm", &data->x, &data->y);
				mlx_put_image_to_window(data->mlx, data->wind, data->img, i * SIZE_, j * SIZE_);
				b = 1;
			}
			i++;
		}
		j++;
	}
}

void save_walls_position(t_data *data)
{
	int i = 0;
	int j = 0;
	int z = 0;

	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
			{
				data->info.walls[z].x = i;
				data->info.walls[z].y = j;
				z++;
			}
			i++;
		}
		j++;
	}
}

int main(void)
{
	t_data data;
	initial(&data);
	background(&data);
	data.info.walls = malloc(sizeof(t_point) * data.info.blocks);
	save_walls_position(&data);
	mlx_loop_hook(data.mlx, draw, &data);
	mlx_hook(data.wind, 3, 0, keyprelease, &data);
	mlx_hook(data.wind, 2, 0, keypress, &data);
	mlx_loop(data.mlx);
}
