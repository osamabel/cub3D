/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:10:30 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/12 14:54:26 by obelkhad         ###   ########.fr       */
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
	if (x < data->col && x >= 0 && y < data->row && y >= 0)
		return (1);
	return (0);
}

char is_wall(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}

int	check_wall(t_data *data, char status)
{
	float	x = 0;
	float	y = 0;
	float	size_player = SIZE_PLYR;
	float	size = SIZE_;

	if (status == 'S')
	{
		x = data->player.x + cos(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection + WALL_DIFF;
		y = data->player.y + -sin(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection + WALL_DIFF;
	}
	if (status == 'W')
	{
		x = data->player.x + cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection + WALL_DIFF;
		y = data->player.y + -sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection + WALL_DIFF;
	}
	if (x - data->player.x > 0)
		x += size_player / size + WALL_DIFF;
	if (y - data->player.y > 0)
		y += size_player / size + WALL_DIFF;
	return (is_wall(data, (int)x, (int)y));
}

int	mini_map_range(int x, int y)
{
	return(x > SIZE_ && x < SIZE_ * MINI_MAP_WIDTH && y > SIZE_ && y < SIZE_ * MINI_MAP_HEIGHT);
}