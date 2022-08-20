/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:59:35 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/20 15:21:56 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*extract_path(char *line)
{
	int		len;
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	len = i;
	while (line[len] && line[len] != '\n')
		len++;
	return (ft_substr(line, i, len - i));
}

int	extract_color(t_data *data, char *line)
{
	int		color[3];
	char	**p;
	int		i;
	int		j;

	p = ft_split2(line, ',');
	i = 0;
	while (p[i])
		i++;
	if (i != 3)
		ft_error(data, "Error: RGB color value is not ");
	i = -1;
	while (p[++i])
	{
		j = -1;
		while (p[i][++j])
		{
			if (!ft_isdigit(p[i][j]) && p[i][j] != ' ')
				ft_error(data, "Error: RGB color value is not valid");
		}
		color[i] = ft_atoi(p[i]);
		if (color[i] < 0 || color[i] > 255)
			ft_error(data, "Error: RGB value is out of rang.");
	}
	ft_free(p);
	return ((color[0] << 16) + (color[1] << 8) + color[2]);
}

void	meta_data(t_data *data, char *line)
{
	int	i;

	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O')
		data->texture.NO = extract_path(&line[i + 2]);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		data->texture.SO = extract_path(&line[i + 2]);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		data->texture.WE = extract_path(&line[i + 2]);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		data->texture.EA = extract_path(&line[i + 2]);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		data->texture.C = extract_color(data, &line[i + 1]);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		data->texture.F = extract_color(data, &line[i + 1]);
}

int	check_for_imposters(t_data *data, char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	if (line[0] == '\n')
		ft_error(data, "map must not separated by one or more empty line(s)");
	while (i < len - 1)
	{
		if (line[i] != ' ' && line[i] != '1'
			&& line[i] != '0' && !is_player(line[i]))
			ft_error(data, "there is one imposter among us");
		i++;
	}
	return (1);
}

void	map_parsing(t_data *data, char *line, char **tmp_map, int fd)
{
	char	*tmp;

	if (is_texture(line))
		meta_data(data, line);
	else if (line[0] != '\n')
	{
		if (!data->texture.NO || !data->texture.SO || !data->texture.WE
			|| !data->texture.EA || !data->texture.C || !data->texture.F)
			ft_error(data, "Error: some texture data info are missing");
		while (line)
		{
			if (check_for_imposters(data, line))
			{
				if (data->col < (int)ft_strlen(line))
					data->col = ft_strlen(line);
				data->row++;
				tmp = *tmp_map;
				*tmp_map = ft_strjoin(*tmp_map, line);
				free(tmp);
			}
			free(line);
			line = get_next_line(fd);
		}
	}
}
