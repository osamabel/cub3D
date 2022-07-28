/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 00:07:20 by obelkhad          #+#    #+#             */
/*   Updated: 2022/07/26 10:03:10 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*node;
	int		counter;

	counter = 1;
	if (!lst)
		return (0);
	node = lst;
	while (node->next)
	{
		counter++;
		node = node->next;
	}
	return (counter);
}
