/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:39:51 by obelkhad          #+#    #+#             */
/*   Updated: 2021/11/16 14:23:21 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_letter(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] && c != set[i])
		i++;
	if (set[i] == c)
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (ft_letter(set, s1[i]) && s1[i])
		i++;
	j = ft_strlen(s1) - 1;
	if (i == j + 1)
		return (ft_strdup(""));
	while (j > i && ft_letter(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
