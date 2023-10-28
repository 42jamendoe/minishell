/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_str_is_env(char *env_itens, char *env_to_test)
{
	size_t len;

	len = ft_strlen(env_to_test);
	
	if (!ft_strncmp(env_itens, env_to_test, len) && env_itens[len + 1] == '=' && \
	env_to_test[len + 1] == '\0')
		return(1);
	return (0);

}


/* char **ft_copy_remain(t_shell *shell, char **env)
{
	int i;
	int j;
	char **new_env;

	i = 0;
	j = 0;
	while (shell->env[i])
	{
		while (env[j])
		{
			if (!ft_str_is_env(shell->env[i], env[j]))
				new_env[i] = shell->env[i];
			else
				free(shell->env[i]);
			j++;
		}
		i++;
	}
	return (new_env);
}*/

char **ft_build_new_env(t_shell *shell, char **env, int j)
{
	int i;
	char **new_env;

	i = 0;
	while (shell->env[i])
		i++;
	new_env = (char **) malloc (sizeof(char *) * (i - j));
	i = 0;
	while (shell->env[i])
	{
		j = 0;
		while (env[j])
		{
			if (!ft_str_is_env(shell->env[i], env[j]))
			{
				new_env[i] = shell->env[i + j];
				j++;
			}
			else
				free(shell->env[i + j]);
		}
		i++;
	}
	return (new_env);
}


int	ft_arg_validate_unset(char **env)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!env[i])
		return (EXIT_SUCCESS);
	while (env[i])
	{
		while (env[i][j] != '\0')
		{
			if (!ft_isvalidname(env[i][j]))
			{
				ft_putstr_fd(env[i], STDERR_FILENO);
				ft_putstr_fd(": not a valid identifier", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_shell *shell, char **env)
{
	char **new_env;
	int i;
	int j;

	i = 1;
	j = 0;
	if (ft_arg_validate_unset(env))
		return (EXIT_FAILURE);
	else
	{
		while (env[i])
		{
			if (!getenv(env[i]))
				j++;
		}
		new_env = ft_build_new_env(shell, env, j);
		free(shell->command_list);
		shell->env = new_env;
	}
	return (0);
}
