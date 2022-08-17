/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:59:35 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/17 15:22:41 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void ft_free(char **table)
{
	int i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

void	ft_error(t_data *data, char *msg)
{
	ft_putendl_fd(msg, 2);
	// free(data->texture.C);
	// free(data->texture.F);
	free(data->texture.NO);
	free(data->texture.SO);
	free(data->texture.WE);
	free(data->texture.EA);
	exit(0);
}

char	*extractText(char *line)
{
	char *info;
	int len;

	len = 0;
	while(line[len] != '\n')
		len++;
	info = ft_substr(line, 0, len);
	return (info);
}

int	extractColor(t_data *data,char *line)
{
	int color[3];
	char	**p;
	int i;
	// int c;
	int j;

	p = ft_split(line, ',');
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
	}
	printf("%d,%d,%d\n", color[0], color[1], color[2]);
	return ((color[0] << 16) + (color[1] << 8) + color[2]);
}

void	meta_data(t_data *data, char *line)
{
	int i;

	i = 0;
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		while (line[i + 2] == ' ')
			i++;
		data->texture.NO = extractText(&line[i + 2]);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		while (line[i + 2] == ' ')
			i++;
		data->texture.SO = extractText(&line[i + 2]);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		while (line[i + 2] == ' ')
			i++;
		data->texture.WE = extractText(&line[i + 2]);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		while (line[i + 2] == ' ')
			i++;
		data->texture.EA = extractText(&line[i + 2]);
	}
	else if (line[i] == 'C')
	{
		while (line[i + 1] == ' ')
			i++;
		data->texture.C = extractColor(data, &line[i + 1]);
	}
	else if (line[i] == 'F')
	{
		while (line[i + 1] == ' ')
			i++;
		data->texture.F = extractColor(data, &line[i + 1]);
	}
}

int	checkForImposter(t_data *data, char *line)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(line);
	if (line[0] == '\n')
		ft_error(data, "map must not separated by one or more empty line(s)");
	while(i < len - 1)
	{
		if (line[i] != ' ' && line[i] != '1'
			&& line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != 'D')
		{
			printf("_%c_\n", line[i]);
			ft_error(data, "there is one imposter among us");
		}
		i++;
	}
	return (1);
}

int realLenght(char *line)
{
	int spcs;
	int charachters;
	int lastSpaces;
	int i;
	int j;

	spcs = 0;
	charachters = 0;
	lastSpaces = 0;
	i = 0;
	j = 1;
	while(line[i] && line[i] != '\n')
	{
		while (line[i] == ' ')
		{
			i++;
			spcs++;
		}
		while (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || line[i] == 'D')
		{
			i++;
			charachters++;
		}
	}
	while (line[i - j] == ' ')
	{
		lastSpaces++;
		j++;
	}
	return (spcs + charachters - lastSpaces);
}

char *realline(char *line)
{
	char *mapLine;
	int	len;
	int	i;

	i = -1;

	len = realLenght(line);
	mapLine = malloc(len * sizeof(char) + 1);
	while (++i < len)
		mapLine[i] = line[i];
	mapLine[i] = 0;
	return (mapLine);
}

// void	storeMap(t_data *data, char *line)
// {
// 	char **newMap;
// 	int i;
// 	i = 0;
// 	newMap = malloc((data->mapLen + 2) * sizeof(char *));
// 	if (data->mapLen)
// 	{
// 		while (i < data->mapLen)
// 		{
// 			newMap[i] = ft_strdup(data->map[i]);
// 			i++;
// 		}
// 	}
// 	newMap[i++] = realline(line);
// 	newMap[i] = NULL;
// 	if (data->mapLen != 0)
// 		ft_free(data->map);
// 	data->map = newMap;
// 	data->mapLen++;
// }

void	map_parsing(t_data *data)
{
	char	*line;
	int	fd;
	int x;

	x = 0;
	data->mapLen = 0;
	if ((fd = open(data->mapath, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error: ", 2);
		perror(data->mapath);
		exit(1);
	}
	line = get_next_line(fd);
	data->mapLen = 0;
	while (line)
	{
		if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
			|| line[0] == 'E' || line[0] == 'F' || line[0] == 'C')
		{
			meta_data(data, line);
			x++;
		}
		else if (line[0] != '\n')
		{

			if (x != 6)
				ft_error(data, "tha map content should be the last thing");
			while (line)
			{
				if (checkForImposter(data, line))
					data->map[data->mapLen++] = realline(line);
				free(line);
				line = get_next_line(fd);
			}
			break;
		}
		free(line);
		line = get_next_line(fd);
	}
	checkWalls(data);
}