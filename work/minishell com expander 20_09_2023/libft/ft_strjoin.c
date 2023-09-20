/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:25:04 by jamendoe          #+#    #+#             */
/*   Updated: 2022/11/12 18:25:06 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*sj;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	sj = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!sj)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		sj[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		sj[i + j] = s2[j];
		j++;
	}
	sj[i + j] = '\0';
	return (sj);
}
/*
Function name 		ft_strjoin
Prototype 			char *ft_strjoin(char const *s1, char const *s2);
Turn in files 		-
Parameters 			s1: The prefix string.
					s2: The suffix string.
Return value 		The new string.
					NULL if the allocation fails.
External functs. 	malloc
Description 		Allocates (with malloc(3)) and returns a new
					string, which is the result of the concatenation
					of ’s1’ and ’s2’.
*/