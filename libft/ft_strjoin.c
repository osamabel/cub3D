/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hadd <ael-hadd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:55:23 by obelkhad          #+#    #+#             */
/*   Updated: 2022/08/19 17:13:22 by ael-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*news;
	int		inews;
	int		is;

	is = 0;
	inews = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	news = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!news)
		return (0);
	while (s1[is])
		news[inews++] = s1[is++];
	is = 0;
	while (s2[is])
		news[inews++] = s2[is++];
	news[inews] = 0;
	return (news);
}
