/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalidname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:36:49 by jamendoe          #+#    #+#             */
/*   Updated: 2022/11/02 18:36:52 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	ft_isvalidname(int c)
{
	return ((c == '_') || \
	(c >= 'A' && c <= 'Z') || \
	(c >= 'a' && c <= 'z') || \
	(c >= '0' && c <= '9'));
}
/*
ft_isvalidname checks for an alphanumeric character
valid for environment VARIABLES NAMES;
The values returned are > 0 if the character c falls into the
tested class, and 0 if not
*/