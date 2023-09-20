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

	while (shell->env_list)
	{
		if (shell->env_list->next)
			current = shell->env_list->next;
		else
			current = NULL;
		free(shell->env_list->name);
		free(shell->env_list->value);
		free(shell->env_list);
		shell->env_list = current;
	}
}

void	ft_add_new_item(t_shell *shell, t_env *item)
{
	t_env	*tmp;

	tmp = shell->env_list;
	if (!shell->env_list)
		shell->env_list = item;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = item;
	}
}

t_env	*ft_new_env_item(char *value)
{
	size_t	start;
	size_t	length;
	char	*name_tmp;
	char	*value_tmp;
	t_env	*item;

	start = 0;
	length = ft_strlen(value);
	item = (t_env *) malloc (sizeof(t_env));
	if (!item)
		return (NULL);
	name_tmp = ft_substr(value, start, ft_cstr(value, '='));
	value_tmp = ft_substr(value, ft_cstr(value, '=') + 1, \
	length - ft_cstr(value, '=') - 1);
	item->name = name_tmp;
	item->value = value_tmp;
	item->next = NULL;
	return (item);
}
