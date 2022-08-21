/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:41:16 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/21 16:23:33 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	ft_free(char **table)
{
	int	i;

	i = -1;
	if (table)
		while (table[++i])
			free(table[i]);
	free(table);
}

void	ft_exit(t_data *data, char *msg)
{
	ft_putendl_fd(msg, 2);
	free(data->texture.no);
	free(data->texture.so);
	free(data->texture.we);
	free(data->texture.ea);
	ft_free(data->map);
	exit(1);
}

int	color_convert(char *buff, int lenght, int i, int j)
{
	int	pixel;
	int	color;

	pixel = (j * lenght) + (i * 4);
	color = buff[pixel + 0];
	color += buff[pixel + 1] << 8;
	color += buff[pixel + 2] << 16;
	return (color);
}

int	is_transparent(t_data *data, int pixel)
{
	return (data->texture.gun_buff[pixel + 0] == 0 && \
	data->texture.gun_buff[pixel + 1] == 0 && \
	data->texture.gun_buff[pixel + 2] == 0);
}
