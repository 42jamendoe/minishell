/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"

int	ft_list_lenght(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		i++;
	return (i);
}

int	ft_transf_vars(t_shell *shell, char **new_env, int valid, int z)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[z + valid] = NULL;
	return (i);
}

void	ft_add_new_vars(t_shell *shell, t_cmd *tmp_cmd, char **new_env)
{
	int	z;
	int	position;
	int	i;

	z = 1;
	i = 0;
	while (tmp_cmd->sim_cmd[z])
	{
		position = ft_check_env_item(shell, tmp_cmd->sim_cmd[z], &i);
		if (position < 0)
			new_env[i + z - 1] = tmp_cmd->sim_cmd[z];
		else
		{
			new_env[position] = tmp_cmd->sim_cmd[z];
			i--;
		}
		z++;
	}
}

int	ft_env_with_declare(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->env[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (shell->env[i][j] != '\0')
		{
			ft_putchar_fd(shell->env[i][j], STDOUT_FILENO);
			if (shell->env[i][j] == '=')
				ft_putchar_fd('\"', STDOUT_FILENO);
			j++;
		}
		ft_putchar_fd('\"', STDOUT_FILENO);
		ft_putendl_fd("", STDOUT_FILENO);	
		i++;
	}
	return (EXIT_SUCCESS);
}
