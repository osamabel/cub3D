/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 16:12:35 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/17 11:46:28 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	read_map(t_data *data)
{
	int fd;
	if ((fd = open(data->mapath, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error: ", 2);
		perror(data->mapath);
		exit(1);
	}
	char *line = get_next_line(fd);
	while (line)
	{
		if (data->col < (int)ft_strlen(line))
			data->col = ft_strlen(line);
		data->row++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	data->map = malloc(sizeof(char*) * (data->row + 1));
	data->map[data->row] = NULL;
	map_parsing(data);
}

void start_connection(t_data *data)
{
	data->mlx = mlx_init();
	data->wind = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void	initial(t_data *data)
{
	data->player.turndirection = 0;
	data->player.walkdirection = 0;
	data->player.sidedirection = 0;
	data->player.rotatespeed = ROTATE_SPEED;
	data->player.walkspeed = WALK_SPEED;
	data->row = 0;
	data->col = 0;
	read_map(data);
	printf("> %d\n",data->texture.C);
	printf("> %d\n",data->texture.F);
	start_connection(data);
	data->texture.wall_NO = mlx_xpm_file_to_image(data->mlx, data->texture.NO,&data->texture.wall_w, &data->texture.wall_h);
	data->texture.wall_SO = mlx_xpm_file_to_image(data->mlx, data->texture.SO,&data->texture.wall_w, &data->texture.wall_h);
	data->texture.wall_EA = mlx_xpm_file_to_image(data->mlx, data->texture.WE,&data->texture.wall_w, &data->texture.wall_h);
	data->texture.wall_WE = mlx_xpm_file_to_image(data->mlx, data->texture.EA,&data->texture.wall_w, &data->texture.wall_h);
	printf("> %d, %d\n",data->texture.wall_w, data->texture.wall_h);
	data->texture.Door = mlx_xpm_file_to_image(data->mlx, "images/W/123.xpm",&data->texture.door_w, &data->texture.door_h);
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