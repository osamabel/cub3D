/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:36:13 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/16 14:41:58 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_isAllOne(char *line)
{
	int i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] != '1' && line[i] != ' ')
				return (0);
			i++;
		}
	}
	return (1);
}

int	checkBorders(char *line)
{
	int i;

	i = 0;
	if (!line[0])
		return (1);
	while (line[i] == ' ')
		i++;
	if (line[i] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	return (1);
}

int	firstLine(t_data data, int index)
{
	
	int i;

	i = -1;
	if (index == 0)
	{
		while (data.map[++i])
			if (data.map[i][0])
				return (i);
	}
	else
	{
		while (data.map[--data.mapLen])
			if (data.map[data.mapLen][0])
				return (data.mapLen);
	}
	return (-1);
}

void	checkWalls(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	if (!ft_isAllOne(data->map[firstLine(*data, 0)]))
		ft_error(data, "the map should be surrounded by walls");
	if (!ft_isAllOne(data->map[firstLine(*data, 1)]))
		ft_error(data, "the map should be surrounded by walls");
	while (data->map[i])
	{
		j = 0;
		if (data->map[i][0] && ft_strlen(data->map[i]) < ft_strlen(data->map[i - 1]) && !ft_isAllOne(&data->map[i - 1][ft_strlen(data->map[i])]))
			ft_error(data, "the map should be surrounded by walls");
		if (!checkBorders(data->map[i]))
			ft_error(data, "the map should be surrounded by walls");
		if (!data->map[i][0] && (!ft_isAllOne(data->map[i - 1]) || !ft_isAllOne(data->map[i + 1])))
		{
			ft_error(data, "the map should be surrounded by walls");
		}
		while (data->map[i][j])
		{
			if (data->map[i][0] && data->map[i - 1][0] && data->map[i][j] == ' ' && (data->map[i - 1][j] != ' ' && data->map[i - 1][j] != '1') && (data->map[i][j - 1] != ' ' && data->map[i - 1][j + 1] != '1'))
				ft_error(data, "the map should be surrounded by walls");
			else if ((data->map[i][j] == '0' || data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W') && data->map[i - 1][j] == ' ')
				ft_error(data, "the map should be surrounded by walls");
			j++;
		}
		i++;
	}
}