/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:36:53 by obelkhad          #+#    #+#             */
/*   Updated: 2021/11/15 14:53:53 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;
	size_t			z;

	i = 0;
	z = 0;
	if (!*needle)
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		j = 0;
		i = z;
		if (haystack[i] == needle[0])
		{
			z = i;
			while (needle[j] && needle[j] == haystack[i] && i++ < len)
			{
				j++;
			}
			if (needle[j] == '\0')
				return ((char *)haystack + z);
		}
		z++;
	}
	return (0);
}
