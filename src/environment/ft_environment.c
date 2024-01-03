/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 15:36:11 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	ft_prepare_env(t_shell *shell, char **envp)
{
	shell->env = NULL;
	if (ft_create_env(shell, envp))
	{
		ft_putendl_fd("minishell: can't create environment", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
}

int	ft_create_env(t_shell *shell, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **) malloc (sizeof(char *) * (i + 1));
	if (!new_env)
		return (-1);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!(new_env[i]))
			ft_clean_env_invalid(new_env, i);
		i++;
	}
	new_env[i] = NULL;
	shell->env = new_env;
	return (0);
}
