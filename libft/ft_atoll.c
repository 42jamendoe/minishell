/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:40:55 by jamendoe          #+#    #+#             */
/*   Updated: 2022/11/17 20:57:56 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

long long	ft_atoll(const char *str)
{
	long long	res;
	int			signal;
	int			i;

	res = 0;
	signal = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
	str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i += 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i += 1;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i] - '0');
		i += 1;
	}
	return (res * signal);
}
/*
The  atoi() function converts the initial portion of the string pointed
to by nptr to int.  The behavior is the same as
strtol(nptr, NULL, 10);
except that atoi() does not detect errors.

The atol() and atoll() functions behave the same as atoi(), except that
they  convert the initial portion of the string to their return type of
long or long long.
atoi() return the converted value.
*/
