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
#include "../includes/minishell.h"

int	ft_create_env(t_shell *shell, char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **) malloc (sizeof(char *) * i);
	if (!new_env)
		ft_clean();
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!(new_env[i]))
			ft_clean();
		i++;
	}
	shell->env = new_env;
	return (0);
}
