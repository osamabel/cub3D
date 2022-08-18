/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:18:45 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/17 14:41:23 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/* IMPORTANT: This is a special ft_split function 
					that developed to meets our needs in cub3D project.*/

static int	wcount(char const *s, char c)
{
	int	n;
	int	i;

	i = 0;
	n = 1;
	while (s[i])
		if (s[i++] == c)
			n++;
	return (n + 1);
}

static int	spliting_problem(char **result, int n)
{
	if (!result[n])
	{
		while (n >= 0)
			free (result[n--]);
		free (result);
		return (1);
	}
	return (0);
}

static char	**str_to_split(char **result, char const *str, char c)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	j = 0;
	word = 0;
	while (i < (int)ft_strlen(str))
	{
		while (str[j] && str[j] != '\n' && str[j] != c)
			j++;
		if (str[j] == c || !str[j] || str[j] == '\n')
		{
			result[word++] = ft_substr(str, i, j - i);
			if (spliting_problem(result, word - 1))
				return (0);
			j++;
			i = j;
		}
	}
	result[word] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**split_str;

	if (!s)
		return (0);
	split_str = NULL;
	split_str = (char **) malloc((wcount(s, c) + 1) * sizeof(char *));
	if (!split_str)
		return (0);
	return (str_to_split(split_str, s, c));
}
