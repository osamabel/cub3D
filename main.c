/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:55:04 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/04 20:27:30 by obelkhad         ###   ########.fr       */
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

void	draw_ray(t_data *data, float _x, float _y, char *color, void *img)
{
	float Px = data->player.x * SIZE_ + SIZE_PLYR/2,Py = data->player.y * SIZE_ + SIZE_PLYR/2;
	float dx = _x - Px,dy = _y - Py,step,xin,yin,x = Px,y = Py,l=0;

	img = mlx_xpm_file_to_image(data->mlx, color, &data->x, &data->y);
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
		mlx_put_image_to_window(data->mlx, data->wind, img, x, y);
		l++;
	}
}

float min_ray(float _h, float _v)
{
	if (_h > _v)
		return (_v);
	return (_h);
}

int	wall_check(t_data *data)
{
	float	x;
	float	y;
	x = data->player.x * SIZE_ + SIZE_PLYR/2;
	y = data->player.y * SIZE_ + SIZE_PLYR/2;
	x += cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	y += -sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	x = (int)(x / SIZE_) * SIZE_;
	y = (int)(y / SIZE_) * SIZE_;
	printf("P[%f, %f]\n",data->player.x, data->player.y);
	printf("[%d, %d]\n",(int)x / SIZE_, (int)y/ SIZE_);
	printf("[%f, %f]\n",x, y);
	printf("[%c]\n\n",data->map[(int)x / SIZE_][(int)y / SIZE_]);
	if (data->map[(int)y / SIZE_][(int)x / SIZE_] == '1')
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
	if (data->player.turndirection)
		data->player.rotatedirection += data->player.turndirection * data->player.rotatespeed;
	float angle = data->player.rotatedirection;
	if (data->player.turndirection || data->player.walkdirection || data->player.sidedirection)
	{
		data->player.ray.h_x = data->player.x * SIZE_ + SIZE_PLYR/2;
		data->player.ray.h_y = data->player.y * SIZE_ + SIZE_PLYR/2;
		data->player.ray.v_x = data->player.x * SIZE_ + SIZE_PLYR/2;
		data->player.ray.v_y = data->player.y * SIZE_ + SIZE_PLYR/2;
		mlx_clear_window(data->mlx, data->wind);
		re_background(data);
		
		

		
		horizontal_points(data, angle);
		vertical_points(data, angle);
		if (data->player.ray.v_distance < data->player.ray.h_distance)
		{
			printf("Direct = (%f, %f)\n",data->player.ray.v_x, data->player.ray.v_y);
			draw_ray(data, data->player.ray.v_x,data->player.ray.v_y, "images/red.xpm",data->ray_v);
		}
		else
		{
			printf("Direct = (%f, %f)\n",data->player.ray.h_x, data->player.ray.h_y);
			draw_ray(data, data->player.ray.h_x,data->player.ray.h_y, "images/blue.xpm",data->ray_h);
		}
		data->player_img = mlx_xpm_file_to_image(data->mlx, "images/player_3.xpm", &data->x, &data->y);
		mlx_put_image_to_window(data->mlx, data->wind, data->player_img, data->player.x * SIZE_, data->player.y * SIZE_);
		mlx_destroy_image(data->mlx, data->player_img);
	}
}

int draw(t_data *data)
{
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
