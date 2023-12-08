/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:21:26 by jamendoe          #+#    #+#             */
/*   Updated: 2022/11/12 18:21:30 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

long long	ft_digits(long long n)
{
	long long	dn;

	dn = 1;
	if (n < 0)
		dn++;
	while (n / 10)
	{
		n = n / 10;
		dn++;
	}
	return (dn);
}

void	ft_write(char *c, int n, int dn)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		c[0] = '-';
	}
	else
		i = 0;
	while (dn >= i)
	{
		c[dn] = n % 10 + 48;
		n = n / 10;
		dn--;
	}
}

char	*ft_lltoa(long long n)
{
	char	*c;
	int		dn;

	dn = ft_digits(n);
	c = (char *) malloc((dn + 1) * sizeof(char));
	if (!c)
		return (NULL);
	c[dn--] = '\0';
	ft_write(c, n, dn);
	return (c);
}

/*
Function name       ft_lltoa
Prototype           char *ft_lltoa(int n);
Turn in files       -
Parameters          n: the long long to convert.
Return value        The string representing the long long.
					NULL if the allocation fails.
External functs.    malloc
Description         Allocates (with malloc(3)) and returns a string
					representing the long long received as an argument.
					Negative numbers must be handled.
*/