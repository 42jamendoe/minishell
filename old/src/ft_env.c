/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <editline/readline.h>

void	ft_clean_env_list(t_env *list)
{
	t_env	*current;

	while (list)
	{
		if (list->next)
			current = list->next;
		else
			current = NULL;
		free(list->name);
		free(list->value);
		free(list);
		list = current;
	}
}

t_env	*ft_add_new_item(t_env *list, t_env *new)
{
	t_env	*tmp;

	tmp = list;
	if (!list)
		list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (list);
}

t_env	*ft_new_env_item(char *item)
{
	unsigned int	start;
	size_t			lenght;
	char			*name_tmp;
	char			*value_tmp;
	t_env			*list;

	start = 0;
	lenght = ft_strlen(item);
	list = (t_env *) malloc (sizeof(t_env));
	name_tmp = ft_substr(item, start, ft_cstr(item, '='));
	value_tmp = ft_substr(item, ft_cstr(item, '=') + 1, \
	lenght - ft_cstr(item, '=') - 1);
	list->name = name_tmp;
	list->value = value_tmp;
	list->status = 1;
	list->next = NULL;
	return (list);
}
