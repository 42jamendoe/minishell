/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:27:16 by jamendoe          #+#    #+#             */
/*   Updated: 2022/11/12 18:27:18 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sp;
	size_t	strlen;
	size_t	i;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (NULL);
	if (len > strlen - start)
		len = strlen - start;
	sp = (char *) malloc (sizeof(char) * (len + 1));
	if (!sp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sp[i] = s[i + start];
		i++;
	}
	sp[i] = '\0';
	return (sp);
}
/*Function name:	ft_substr
Prototype:			char *ft_substr(char const *s, \
unsigned int start, size_t len);
Turn in files: 		-
Parameters:			s: The string from which to create the substring.
					start: The start index of the substring in the string ’s’.
					len: The maximum length of the substring.
Return value:		The substring.
					NULL if the allocation fails.
External functs:	malloc
Description:		Allocates (with malloc(3)) and returns a substring
					from the string ’s’.
					The substring begins at index ’start’ and is of
					maximum size ’len’.*/
