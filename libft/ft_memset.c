/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:01:44 by obelkhad          #+#    #+#             */
/*   Updated: 2021/11/15 14:23:16 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t	len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)buf)[i] = (unsigned char) ch;
		i++;
	}
	return (buf);
}
