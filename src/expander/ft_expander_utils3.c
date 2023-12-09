/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

char	*ft_match_env_value(t_shell *shell, char *env_name)
{
	int		i;
	char	*env_value;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_str_is_env(shell->env[i], env_name))
			i++;
		else
		{
			env_value = ft_get_env_value(shell->env[i]);
			free(env_name);
			return (env_value);
		}
	}
	return (NULL);
}

char	*ft_expand_dollar(t_shell *shell, char *arg, int anchor, int *position)
{
	char	*env_name;
	char	*env_value;

	env_value = NULL;
	env_name = ft_substr(arg, anchor, (*position) - anchor);
	if (!env_name)
		return (NULL);
	if ((*position) - anchor == 1)
	{
		(*position)++;
		return (env_name);
	}
	else
	{
		env_value = ft_match_env_value(shell, env_name);
		if (!env_value)
			return (NULL);
		return (env_value);
	}
	return (NULL);
}

char	*ft_join_not_null(char *join, char *expanded)
{
	if (join)
		return (join);
	free(expanded);
	return (NULL);
}
