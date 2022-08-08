/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:12:35 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/08 09:23:48 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	read_map(t_data *data)
{
	int len = 0;
	int fd = open("map.cub", O_RDONLY);
	char *line = get_next_line(fd);
	data->col = ft_strlen(line) - 1;
	while (line)
	{
		data->row++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	data->map = malloc(sizeof(char*) * (data->row + 1));
	data->map[data->row] = 0;
	len = 0;
	fd = open("map.cub", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (len < data->row - 1)
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

	data->player.turndirection= 0;
	data->player.walkdirection= 0;
	data->player.sidedirection= 0;
	data->player.rotatespeed = .05;
	data->player.walkspeed = .05;


	data->row = 0;
	data->col = 0;
	read_map(data);
	data->mlx = mlx_init();
	data->wind = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
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

int	point_in_range(t_data *data, int x, int y)
{
	if (x < data->col && x >= 0 && y < data->row && y >= 0)
		return (1);
	return (0);
}

int is_wall(t_data *data, int x, int y)
{
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}