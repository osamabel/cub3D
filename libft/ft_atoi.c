/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:03:10 by obelkhad          #+#    #+#             */
/*   Updated: 2021/11/16 11:55:55 by obelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	testlong(unsigned long long nb, int sign)
{
	unsigned long long	ll;

	ll = 9223372036854775807;
	if (nb > (ll + 1) && sign == -1)
		return (0);
	if (nb > ll && sign == 1)
		return (-1);
	return (1);
}

static int	ft_ispace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v'
		|| c == '\f');
}

int	ft_atoi(const char *str)
{
	int					i;
	int					minus;
	unsigned long long	result;
	int					is_long;

	minus = 1;
	result = 0;
	i = 0;
	while (str[i] && ft_ispace(str[i]))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i++] == '-')
			minus = -minus;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i++] - '0';
		is_long = testlong(result, minus);
		if (is_long != 1)
			return (is_long);
	}
	return (result * minus);
}
