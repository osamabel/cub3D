/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:10:30 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/20 09:52:48 by ael-hadd         ###   ########.fr       */
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

char is_wall(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		return ('W');
	if (data->map[y][x] == 'D')
		return ('D');
	return (0);
}

int	is_texture(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (1);
	else
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
	if (is_wall(data, (int)x, (int)y) == 'W')
		return (1);
	return (0);
}

int	mini_map_range(int x, int y)
{
	return(x > SIZE_ && x < SIZE_ * MINI_MAP_WIDTH && y > SIZE_ && y < SIZE_ * MINI_MAP_HEIGHT);
}