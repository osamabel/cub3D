/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:36:13 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/20 15:33:40 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_is_all_1(char *line)
{
	int	i;

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

int	check_borders(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line) - 1;
	while (line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (0);
	while (line[len] == ' ')
		len--;
	if (line[len] != '1')
		return (0);
	return (1);
}

int	first_line(t_data data, int index)
{
	int	i;
	int	j;

	i = -1;
	if (!index)
	{
		while (data.map[++i])
		{
			j = -1;
			while (data.map[i][++j])
				if (data.map[i][j] != ' ')
					return (i);
		}
	}
	else
	{
		while (data.map[--data.row])
		{
			j = -1;
			while (data.map[data.row][++j])
				if (data.map[data.row][j] != ' ')
					return (data.row);
		}
	}
	return (-1);
}

void	check_walls1(t_data *data, int i, int j)
{
	if (data->map[i][j] == '0')
	{
		if (data->map[i][j + 1] == ' ' || data->map[i][j - 1] == ' ')
			ft_error(data, "Error: The map must be closed/surrounded by walls");
		if (j > (int)ft_strlen(data->map[i - 1]) - 1
			|| data->map[i - 1][j] == ' ')
			ft_error(data, "Error: The map must be closed/surrounded by walls");
		if (j > (int)ft_strlen(data->map[i + 1]) - 1
			|| data->map[i + 1][j] == ' ')
			ft_error(data, "Error: The map must be closed/surrounded by walls");
	}
	else if (is_player(data->map[i][j]))
	{
		if (data->map[i][j + 1] == ' ' || data->map[i][j - 1] == ' ')
			ft_error(data, "Error: The map must be closed/surrounded by walls");
		if (j > (int)ft_strlen(data->map[i - 1]) - 1
			|| data->map[i - 1][j] == ' ')
			ft_error(data, "Error: The map must be closed/surrounded by walls");
		if (j > (int)ft_strlen(data->map[i + 1]) - 1
			|| data->map[i + 1][j] == ' ')
			ft_error(data, "Error: The map must be closed/surrounded by walls");
	}
}

void	check_walls(t_data *data)
{
	int	i;
	int	j;

	if (!ft_is_all_1(data->map[first_line(*data, 0)]))
		ft_error(data, "Error: The map must be closed/surrounded by walls");
	if (!ft_is_all_1(data->map[first_line(*data, 1)]))
		ft_error(data, "Error: The map must be closed/surrounded by walls");
	i = first_line(*data, 0);
	while (data->map[++i])
	{
		j = -1;
		if (!check_borders(data->map[i]))
			ft_error(data, "Error: The map must be closed/surrounded by walls");
		while (data->map[i][++j])
			check_walls1(data, i, j);
	}
}
