/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 08:55:04 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/18 16:28:52 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_extension(char *path)
{
	if (path && !ft_strcmp(&path[ft_strlen(path) - 4], ".cub"))
		return (0);
	printf("The scene description file must be a .cub file.\n");
	return (1);
}

int update(t_data *data)
{
	t_ray	*ray;

	if (data->player.sidedirection && !check_wall(data, 'S'))
	{
		data->player.x += cos(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
		data->player.y += -sin(data->player.rotatedirection + M_PI_2) * data->player.walkspeed * data->player.sidedirection;
	}
	if (data->player.walkdirection && !check_wall(data, 'W'))
	{
		data->player.x += cos(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
		data->player.y += -sin(data->player.rotatedirection) * data->player.walkspeed * data->player.walkdirection;
	}
	if (data->player.turndirection)
		data->player.rotatedirection += data->player.turndirection * data->player.rotatespeed;
	data->player.rotatedirection += data->player.mouse;
	data->player.mouse = 0;
	mlx_clear_window(data->mlx, data->wind);
	ray = update_ray(data);
	rendring(data, ray);
	mini_map(data, ray);
	sprite_gun(data);
	mlx_put_image_to_window(data->mlx, data->wind, data->img, 0, 0);
	return (0);
}

int main(int ac, char **av)
{
	t_data data;
	if (ac != 2 || check_extension(av[1]))
		return (1);
	data.mapath = av[1];
	initial(&data);
	get_info(&data);
	mlx_loop_hook(data.mlx, update, &data);
	mlx_hook(data.wind, 3, 0, keyprelease, &data);
	mlx_hook(data.wind, 2, 0, keypress, &data);
	// mlx_hook(data.wind,6,0, mouse_hook, &data);
	mlx_loop(data.mlx);
}
