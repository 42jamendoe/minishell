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

void	ft_loop_list(char **shell_list, char **unset_list, char **new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (shell_list[i])
	{
		while (unset_list[j])
		{
			if (!ft_str_is_env(shell_list[i], unset_list[j]))
				new_env[i] = shell_list[i + j - 1];
			else
			{
				free(shell_list[i + j - 1]);
				j++;
			}
			i++;
		}
	}
	new_env[i + j - 1] = NULL;
}

int	ft_check_list(t_shell *shell, char **env_unset)
{
	int	j;
	int	i;
	int	var_exists;

	j = 0;
	var_exists = 0;
	while (shell->env[j])
	{
		i = 1;
		while (env_unset[i])
		{
			if (ft_str_is_env(shell->env[j], env_unset[i]))
				var_exists++;
			i++;
		}
		j++;
	}
	return (var_exists);
}
