/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:12:32 by ael-hadd          #+#    #+#             */
/*   Updated: 2022/08/19 20:04:38 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static	char	**freee(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static	char	**put_split(char const *s, char c)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	**split;

	start = 0;
	end = 0;
	i = 0;
	split = (char **)malloc(sizeof(char *) * (str_count(s, c) + 1));
	if (!split)
		return (NULL);
	while (i < str_count(s, c))
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		split[i++] = ft_substr(s, start, (end - start));
		if (!split[i - 1])
			return (freee(split));
		start = end;
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = put_split(s, c);
	return (split);
}
