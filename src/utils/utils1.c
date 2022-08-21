/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 10:42:29 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/21 15:47:58 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	put_pixel(t_data *data, int color, int alpha)
{
	int	pixel;
	int	x;
	int	y;

	x = data->point.x;
	y = data->point.y;
	pixel = (y * data->line_length) + (x * data->bits_per_pixel / 8);
	if (data->endian == 1 && pixel > 0)
	{
		data->addr[pixel + 0] = alpha;
		data->addr[pixel + 1] = (color >> 16) & 0xFF;
		data->addr[pixel + 2] = (color >> 8) & 0xFF;
		data->addr[pixel + 3] = (color) & 0xFF;
	}
	else if (data->endian == 0 && pixel > 0)
	{
		data->addr[pixel + 0] = (color) & 0xFF;
		data->addr[pixel + 1] = (color >> 8) & 0xFF;
		data->addr[pixel + 2] = (color >> 16) & 0xFF;
		data->addr[pixel + 3] = alpha;
	}
}

int	check_x(t_data *data, float x, float y)
{
	int		check1;
	int		check2;

	if (y < data->player.y)
	{
		check1 = is_wall(data, x, y);
		check2 = is_wall(data, x + 0.4, y);
		if (check1 || check2)
			return (1);
	}
	if (y > data->player.y)
	{
		check1 = is_wall(data, x, y + 0.4);
		check2 = is_wall(data, x + 0.4, y + 0.4);
		if (check1 || check2)
			return (1);
	}
	return (0);
}

int	check_y(t_data *data, float x, float y)
{
	int		check1;
	int		check2;

	if (x < data->player.x)
	{
		check1 = is_wall(data, x, y);
		check2 = is_wall(data, x, y + 0.4);
		if (check1 || check2)
			return (1);
	}
	if (x > data->player.x)
	{
		check1 = is_wall(data, x + 0.4, y);
		check2 = is_wall(data, x + 0.4, y + 0.4);
		if (check1 || check2)
			return (1);
	}
	return (0);
}

int	check_wall(t_data *data, char status)
{
	float	x;
	float	y;

	x = 0;
	y = 0;
	if (status == 'S')
	{
		x = data->player.x + cos(data->player.rotatedirection + M_PI_2) * \
		data->player.walkspeed * data->player.sidedirection;
		y = data->player.y + -sin(data->player.rotatedirection + M_PI_2) * \
		data->player.walkspeed * data->player.sidedirection;
	}
	if (status == 'W')
	{
		x = data->player.x + cos(data->player.rotatedirection) * \
		data->player.walkspeed * data->player.walkdirection;
		y = data->player.y + -sin(data->player.rotatedirection) * \
		data->player.walkspeed * data->player.walkdirection;
	}
	return (check_x(data, x, y) || check_y(data, x, y));
}
