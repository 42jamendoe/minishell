/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"

int	ft_str_is_env(char *env_itens, char *env_to_test)
{
	size_t	len;

	len = ft_strlen(env_to_test);
	if (!ft_strncmp(env_itens, env_to_test, len) && env_itens[len] == \
'=' && env_to_test[len] == '\0')
		return (1);
	return (0);
}

int	ft_adjust_list(char *const *shell_list, char **new_env, int i, int k)
{
	new_env[i] = shell_list[i + k];
	i++;
	return (i);
}

void	ft_loop_list(char **shell_list, char **unset_list, char **new_env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (shell_list[i + k])
	{
		j = 1;
		while (unset_list[j])
		{
			if (ft_str_is_env(shell_list[i + k], unset_list[j]))
			{
				free(shell_list[i + k]);
				k++;
				break ;
			}
			else
				j++;
		}
		if (!unset_list[j])
			i = ft_adjust_list(shell_list, new_env, i, k);
	}
	new_env[i] = NULL;
}

int	ft_check_list(t_shell *shell, char **env_unset)
{
	int	j;
	int	i;
	int	var_exists;

	j = 1;
	var_exists = 0;
	while (env_unset[j])
	{
		i = 0;
		while (shell->env[i])
		{
			if (ft_str_is_env(shell->env[i], env_unset[j]))
			{
				var_exists++;
				break ;
			}
			else
				i++;
		}
		j++;
	}
	return (var_exists);
}

int	ft_position_of_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}
