/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:10:30 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/20 12:32:54 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_pixel(t_data *data,char *buffer, int color, int x, int y, int alpha)
{
	int	pixel;

	pixel = (y * data->line_length) + (x * data->bits_per_pixel/8);
	if (data->endian == 1 && pixel > 0)
    {
        buffer[pixel + 0] = alpha;
        buffer[pixel + 1] = (color >> 16) & 0xFF;
        buffer[pixel + 2] = (color >> 8) & 0xFF;
        buffer[pixel + 3] = (color) & 0xFF;
    }
    else if (data->endian == 0 && pixel > 0)
    {
		buffer[pixel + 0] = (color) & 0xFF;
		buffer[pixel + 1] = (color >> 8) & 0xFF;
		buffer[pixel + 2] = (color >> 16) & 0xFF;
		buffer[pixel + 3] = alpha;
    }
}

int	is_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

int	point_in_range(t_data *data, int x, int y)
{
	if (x < data->col && x >= 0 && y < data->mapLen && y >= 0)
		return (1);
	return (0);
}

int is_wall(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}

int	check_wall(t_data *data, char status)
{
	float	x;
	float	y;
	int	check1;
	int	check2;

	x = 0;
	y = 0;
	if (status == 'S')
	{
		x = data->player.x + cos(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
		y = data->player.y + -sin(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
	}
	if (status == 'W')
	{
		x = data->player.x + cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
		y = data->player.y + -sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	}
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
	if (x < data->player.x)
	{
		check1 = is_wall(data, x , y);
		check2 = is_wall(data, x, y + 0.4);
		if (check1 || check2)
			return (1);
	}
	if (x > data->player.x)
	{
		check1 = is_wall(data, x + 0.4, y );
		check2 = is_wall(data, x + 0.4, y + 0.4);
		if (check1 || check2)
			return (1);
	}
	return (0);
}