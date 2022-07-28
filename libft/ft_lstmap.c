/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:58:31 by obelkhad          #+#    #+#             */
/*   Updated: 2022/07/26 10:03:16 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	void	*ct;
	t_list	*tmp;

	if (!del)
		del = free;
	if (!f || !lst)
		return (NULL);
	result = NULL;
	while (lst)
	{
		ct = f(lst->content);
		tmp = ft_lstnew(ct);
		if (!tmp)
			ft_lstclear(&result, del);
		ft_lstadd_back(&result, tmp);
		lst = lst->next;
	}
	return (result);
}
