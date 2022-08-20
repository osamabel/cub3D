/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:41:16 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/20 09:23:07 by ael-hadd         ###   ########.fr       */
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

void	ft_error(t_data *data, char *msg)
{
	ft_putendl_fd(msg, 2);
	free(data->texture.NO);
	free(data->texture.SO);
	free(data->texture.WE);
	free(data->texture.EA);
	ft_free(data->map);
	exit(1);
}
