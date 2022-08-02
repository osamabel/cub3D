/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:55:04 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/02 14:40:11 by obelkhad         ###   ########.fr       */
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

void	draw_ray(t_data *data, float _x, float _y, char *color)
{
	float Px = data->player.x * SIZE_ + SIZE_PLYR/2,Py = data->player.y * SIZE_ + SIZE_PLYR/2;
	float dx = _x - Px,dy = _y - Py,step,xin,yin,x = Px,y = Py,l=0;

	data->ray = mlx_xpm_file_to_image(data->mlx, color, &data->x, &data->y);
	if (dx >= dy)
	{
		if (dx < 0)
			step = -dx;
		else
			step = dx;
	}
	else
		if (dy < 0)
			step = -dy;
		else
			step = dy;
	xin = dx / step;
	yin = dy / step;
	while (l < step)
	{
		x = x + xin;
		y = y + yin;
		mlx_put_image_to_window(data->mlx, data->wind, data->ray, x, y);
		l++;
	}
}

void	raycasting(t_data *data)
{
	float h_x,h_y,v_x,v_y;
	float h_dx,h_dy,v_dx,v_dy;
	(void)v_x;
	(void)v_y;
	(void)v_dy;
	(void)v_dx;
	// (void)h_x;
	// (void)h_y;
	// (void)h_dy;
	// (void)h_dx;

//horizontal
	// h_x = data->player.ray.h_x;
	// h_y = data->player.ray.h_y;
	// if (sin(data->player.rotatedirection) > 0)
	// 	h_dy = SIZE_ * (int)(h_y/SIZE_);
	// else
	// 	h_dy = SIZE_ * (int)(h_y/SIZE_) + SIZE_;
	// data->player.ray.h_y = h_dy;
	// h_dy = h_y - h_dy;
	// h_dx = h_dy / tan(data->player.rotatedirection);
	// data->player.ray.h_x = h_x + h_dx;
	// data->player.ray.h_dx += h_dx;
	// data->player.ray.h_dy += h_dy;
	// while (data->player.ray.h_x <= data->col * SIZE_ && data->player.ray.h_y <= data->row * SIZE_ && !check_wall_h_points(data, data->player.ray.h_x, data->player.ray.h_y))
	// {
	// 	h_x = data->player.ray.h_x;
	// 	h_y = data->player.ray.h_y;
	// 	if (sin(data->player.rotatedirection) > 0)
	// 		h_dy = SIZE_ * (int)((h_y - 0.1)/SIZE_);
	// 	else
	// 		h_dy = SIZE_ * (int)((h_y + 0.1)/SIZE_);
	// 	data->player.ray.h_y = h_dy;
	// 	h_dy = h_y - h_dy;
	// 	h_dx = h_dy / tan(data->player.rotatedirection);
	// 	data->player.ray.h_x = h_x + h_dx;
	// 	data->player.ray.h_dx += h_dx;
	// 	data->player.ray.h_dy += h_dy;
	// }
	// data->ray = mlx_xpm_file_to_image(data->mlx, "images/blue.xpm", &data->x, &data->y);
	// int i = 0,j = 0;
	// while (j < 5)
	// {
	// 	i = 0;
	// 	while (i < 5)
	// 	{
	// 		mlx_put_image_to_window(data->mlx, data->wind, data->ray, data->player.ray.h_x + i, data->player.ray.h_y + j);
	// 		i++;
	// 	}
	// 	j++;
	// }
	// data->player.ray.h_distance = sqrt(pow(data->player.ray.h_dx, 2) + pow(data->player.ray.h_dy, 2));
	// data->player.ray.h_dx = 0;
	// data->player.ray.h_dy = 0;

//vertical
	v_x = data->player.ray.v_x;
	v_y = data->player.ray.v_y;
	if (cos(data->player.rotatedirection) > 0)
		v_dx = SIZE_ * (int)(v_x/SIZE_) + SIZE_;
	else
		v_dx = SIZE_ * (int)(v_x/SIZE_);
	data->player.ray.v_x = v_dx;
	v_dx = v_x - v_dx;
	v_dy = v_dx / tan(data->player.rotatedirection);
	data->player.ray.v_y = v_y + v_dy;
	data->player.ray.v_dx += v_dx;
	data->player.ray.v_dy += v_dy;
	while (!check_wall_v_points(data, data->player.ray.v_x, data->player.ray.v_y))
	{
		printf("[%f][%f]\n\n",data->player.ray.v_x, data->player.ray.v_y);
		v_x = data->player.ray.v_x;
		v_y = data->player.ray.v_y;
		if (cos(data->player.rotatedirection) > 0)
			v_dx = SIZE_ * (int)((v_y + 0.1)/SIZE_);
		else
			v_dx = SIZE_ * (int)((v_y - 0.1)/SIZE_);
		data->player.ray.v_x = v_dx;
		v_dx = v_x - v_dx;
		v_dy = v_dx / tan(data->player.rotatedirection);
		data->player.ray.v_y = v_y + v_dy;
		data->player.ray.v_dx += v_dx;
		data->player.ray.v_dy += v_dy;
	}
	data->player.ray.v_distance = sqrt(pow(data->player.ray.v_dx, 2) + pow(data->player.ray.v_dy, 2));
	data->player.ray.v_dx = 0;
	data->player.ray.v_dy = 0;
	// data->ray = mlx_xpm_file_to_image(data->mlx, "images/red.xpm", &data->x, &data->y);
	// int i = 0,j = 0;
	// while (j < 5)
	// {
	// 	i = 0;
	// 	while (i < 5)
	// 	{
	// 		mlx_put_image_to_window(data->mlx, data->wind, data->ray, data->player.ray.h_x + i, data->player.ray.h_y + j);
	// 		i++;
	// 	}
	// 	j++;
	// }
}

int check_wall_v_points(t_data *data, float x, float y)
{
	int i = 0;

	y = (int)(y/SIZE_) * SIZE_;
	if (cos(data->player.rotatedirection) > 0)
		x = (int)((x + 0.1)/SIZE_) * SIZE_;
	if (cos(data->player.rotatedirection) < 0)
		x = (int)((x - 0.1)/SIZE_) * SIZE_;
	while(i < data->info.blocks && !(x == data->info.walls[i].x && y == data->info.walls[i].y))
		i++;
	if (i < data->info.blocks)
		return (1);
	return (0);
}

int check_wall_h_points(t_data *data, float x, float y)
{
	int i = 0;

	x = (int)(x/SIZE_) * SIZE_;
	if (sin(data->player.rotatedirection) > 0)
		y = (int)((y - 0.1)/SIZE_) * SIZE_;
	if (sin(data->player.rotatedirection) < 0)
		y = (int)((y + 0.1)/SIZE_) * SIZE_;
	while(i < data->info.blocks && !(x == data->info.walls[i].x && y == data->info.walls[i].y))
		i++;
	if (i < data->info.blocks)
		return (1);
	return (0);
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
	data->player.ray.h_x = data->player.x * SIZE_ + SIZE_PLYR/2;
	data->player.ray.h_y = data->player.y * SIZE_ + SIZE_PLYR/2;
	data->player.ray.v_x = data->player.x * SIZE_ + SIZE_PLYR/2;
	data->player.ray.v_y = data->player.y * SIZE_ + SIZE_PLYR/2;
	if (data->player.turndirection)
		data->player.rotatedirection += data->player.turndirection * data->player.rotatespeed;
	raycasting(data);
	data->player_img = mlx_xpm_file_to_image(data->mlx, "images/person_1.xpm", &data->x, &data->y);
	mlx_put_image_to_window(data->mlx, data->wind, data->player_img, data->player.x * SIZE_, data->player.y * SIZE_);
	// if (data->player.ray.v_distance < data->player.ray.h_distance)
	// {
	// 	printf("LL\n");
	// 	draw_ray(data, data->player.ray.h_x,data->player.ray.h_y, "images/red.xpm");
	// }
	// else
	// {
	// 	printf("1LL\n");
	// 	draw_ray(data, data->player.ray.v_x,data->player.ray.v_y, "images/blue.xpm");
	// }
	// draw_ray(data, data->player.ray.v_x,data->player.ray.v_y);
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
		// int i = 0;
		// while(i < data.info.blocks)
		// {
		// 	printf("Wx = %f / Wy = %f \n",data.info.walls[i].x, data.info.walls[i].y);
		// 	i++;
		// }
	mlx_loop_hook(data.mlx, draw, &data);
	mlx_hook(data.wind, 3, 0, keyprelease, &data);
	mlx_hook(data.wind, 2, 0, keypress, &data);
	mlx_loop(data.mlx);
}
