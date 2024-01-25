/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ignore_equal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:40:55 by jamendoe          #+#    #+#             */
/*   Updated: 2022/11/17 20:57:56 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

int	ft_ignore_equal(const char *str, int index, const char \
*char_list)
{
	int	i;

	i = 0;
	if (!char_list || !str)
		return (0);
	while (char_list[i] != '\0')
	{
		while (str[index] != '\0')
		{
			if (str[index] == char_list[i])
				index++;
			else
				break ;
		}
		i++;
	}
	return (index);
}
/*
The  ft_some_char_in_str() function search any char of the list in the
str.

if to_end is one it search till the end if to end is zero just search that char.
The ft_some_char_in_str() returns 0 if none char of the list appear in the
 string or index from i.
*/
