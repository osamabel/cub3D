/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:12:35 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/10 22:01:33 by obelkhad         ###   ########.fr       */
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
	data->texture.C = 0x00004d;
	data->texture.F = 0x808080;
	data->player.turndirection= 0;
	data->player.walkdirection= 0;
	data->player.sidedirection= 0;
	data->player.rotatespeed = ROTATE_SPEED;
	data->player.walkspeed = WALK_SPEED;


	data->row = 0;
	data->col = 0;
	read_map(data);
	data->mlx = mlx_init();
	data->wind = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->img1 = mlx_xpm_file_to_image(data->mlx, "./images/wall2.xpm",&data->x, &data->y);
	data->wall = mlx_get_data_addr(data->img1, &data->bits_per_pixel, &data->line_length_wall, &data->endian);
}
void	get_info(t_data *data)
{
	int i = 0;
	int j = 0;

	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i] && data->map[j][i] != '\n')
		{
			if (is_player(data->map[j][i]))
			{
				data->player.x = i;
				data->player.y = j;
				data->player.h_x = data->player.x * SIZE_ + SIZE_PLYR/2;
				data->player.h_y = data->player.y * SIZE_ + SIZE_PLYR/2;
				data->player.v_x = data->player.x * SIZE_ + SIZE_PLYR/2;
				data->player.v_y = data->player.y * SIZE_ + SIZE_PLYR/2;
				if (data->map[j][i] == 'N')
					data->player.rotatedirection = M_PI_2;
				if (data->map[j][i] == 'E')
					data->player.rotatedirection = 0;
				if (data->map[j][i] == 'S')
					data->player.rotatedirection = 3 * M_PI_2;
				if (data->map[j][i] == 'W')
					data->player.rotatedirection = M_PI;
			}
			i++;
		}
		j++;
	}
}