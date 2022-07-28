/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:12:35 by obelkhad          #+#    #+#             */
/*   Updated: 2022/07/28 10:43:21 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	read_map(t_data *data)
{
	int len = 0;
	int fd = open("map.cub", O_RDONLY);
	char *line = get_next_line(fd);
	while (line)
	{
		data->col++;
		len = ft_strlen(line);
		if (len - 1 > data->row)
			data->row = len - 1;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	fd = open("map.cub", O_RDONLY);
	line = get_next_line(fd);
	data->map = malloc(sizeof(char*) * (data->col + 1));
	data->map[data->col] = 0;
	len = 0;
	while (line)
	{
		if (len < data->col - 1)
			data->map[len] = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			data->map[len] = ft_strdup(line);
		len++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
}

void	initial(t_data *data)
{
	data->put_in_x = 0;
	data->put_in_y = 0;
	data->row = 0;
	data->col = 0;
	read_map(data);
	data->mlx = mlx_init();
	data->wind = mlx_new_window(data->mlx, data->row * SIZE_, data->col * SIZE_, "Cube3D");
	data->img = mlx_new_image(data->mlx, data->row * SIZE_, data->col * SIZE_);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);

	data->player.movespeed= 0;
	data->player.turndirection= 0;
	data->player.walkdirection= 0;
	data->player.radius = 8;
	data->player.rotatespeed = 1;
	data->player.walkspeed = 2;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	is_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}
