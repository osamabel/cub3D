/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:55:04 by obelkhad          #+#    #+#             */
/*   Updated: 2022/07/30 21:43:19 by obelkhad         ###   ########.fr       */
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
	if (keycode == 13) // ^ W
		data->player.walkdirection = 1;
	if (keycode == 1) // v S
		data->player.walkdirection = -1;
	if (keycode == 0) //  A
		data->player.sidedirection = 1;
	if (keycode == 2) //  D
		data->player.sidedirection = -1;
	return 0;
}



void	raycasting(t_data *data)
{
	float dx,dy;

	dy = data->player.y * SIZE_;
	if (sin(data->player.rotatedirection) > 0)
		data->player.ray.end_y = SIZE_ * (int)(dy/SIZE_);
	if (sin(data->player.rotatedirection) < 0)
		data->player.ray.end_y = SIZE_ * (int)(dy/SIZE_) + SIZE_;
	dy = data->player.y * SIZE_ - data->player.ray.end_y;
	dx = dy / tan(data->player.rotatedirection);
	data->player.ray.dx += dx;
	data->player.ray.dy += dy;
	if (sin(data->player.rotatedirection) > 0)
		data->player.ray.end_x = data->player.x * SIZE_ + dx;
	if (cos(data->player.rotatedirection) < 0 && sin(data->player.rotatedirection) < 0)
		data->player.ray.end_x = data->player.x * SIZE_ + dx + SIZE_PLYR;

	printf("[X = %f, Y = %f]\n",data->player.x * SIZE_, data->player.y * SIZE_);
	printf("[%f]\n",data->player.rotatedirection);
	printf("[endX = %f, endY = %f]\n\n",data->player.ray.end_x, data->player.ray.end_y );
}

void	update_player(t_data *data)
{
	if (data->player.sidedirection)
	{
		data->player.x += cos(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
		data->player.y += -sin(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
	}
	if (data->player.walkdirection)
	{
		data->player.x += cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
		data->player.y += -sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	}
	if (data->player.turndirection)
		data->player.rotatedirection += data->player.turndirection * data->player.rotatespeed;

	raycasting(data);

	data->player_img = mlx_xpm_file_to_image(data->mlx, "images/person_1.xpm", &data->x, &data->y);
	mlx_put_image_to_window(data->mlx, data->wind, data->player_img, data->player.x * SIZE_, data->player.y * SIZE_);
}

int draw(t_data *data)
{
	re_background(data);
	update_player(data);
	return (0);
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
