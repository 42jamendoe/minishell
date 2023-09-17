/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 15:36:11 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clean_env_list(t_shell *shell)
{
	t_env	*current;

	while (shell->list)
	{
		if (shell->list.next)
			current = shell->list.next;
		else
			current = NULL;
		free(shell->list.name);
		free(shell->list.value);
		free(shell->list);
		shell->list = current;
	}
}

void	ft_add_new_item(t_env *list, t_env *new)
{
	t_env	*tmp;

	tmp = shell->list;
	if (!shell->list)
		shell->list = shell->new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = shell->new;
	}
	shell->env_list = shell->list;
}

t_env	*ft_new_env_item(char *item)
{
	unsigned int	start;
	size_t			length;
	char			*name_tmp;
	char			*value_tmp;
	t_env			*list;

	start = 0;
	length = ft_strlen(item);
	list = (t_env *) malloc (sizeof(t_env));
	name_tmp = ft_substr(item, start, ft_cstr(item, '='));
	value_tmp = ft_substr(item, ft_cstr(item, '=') + 1, \
	length - ft_cstr(item, '=') - 1);
	list->name = name_tmp;
	list->value = value_tmp;
	list->status = 1;
	list->next = NULL;
	return (list);
}
