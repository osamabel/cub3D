/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 10:10:30 by obelkhad          #+#    #+#             */
/*   Updated: 2022/07/30 10:20:37 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	re_background(t_data *data)
{
	int i = 0;
	int j = 0;

	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
				mlx_put_image_to_window(data->mlx, data->wind, data->map_gb, i * SIZE_, j * SIZE_);
			else
				mlx_put_image_to_window(data->mlx, data->wind, data->map_wall, i * SIZE_, j * SIZE_);
			i++;
		}
		j++;
	}
}


void	background(t_data *data)
{
	int i = 0;
	int j = 0;

	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == '1')
			{
				data->info.blocks++;
				data->map_gb = mlx_xpm_file_to_image(data->mlx, "images/44449.xpm", &data->x, &data->x);
				mlx_put_image_to_window(data->mlx, data->wind, data->map_gb, i * SIZE_, j * SIZE_);
			}
			else
			{
				data->map_wall = mlx_xpm_file_to_image(data->mlx, "images/fff49.xpm", &data->x, &data->y);
				mlx_put_image_to_window(data->mlx, data->wind, data->map_wall, i * SIZE_, j * SIZE_);
			}
			if (is_player(data->map[j][i]))
			{
				data->player.x = i;
				data->player.y = j;
				if (data->map[j][i] == 'N')
					data->player.rotatedirection = M_PI_2;
				if (data->map[j][i] == 'E')
					data->player.rotatedirection = 0;
				if (data->map[j][i] == 'S')
					data->player.rotatedirection = 3 * M_PI_2;
				if (data->map[j][i] == 'W')
					data->player.rotatedirection = M_PI;
				data->player_img = mlx_xpm_file_to_image(data->mlx, "images/person_1.xpm", &data->x, &data->y);
				mlx_put_image_to_window(data->mlx, data->wind, data->player_img, i * SIZE_, j * SIZE_);
			}
			i++;
		}
		j++;
	}
}