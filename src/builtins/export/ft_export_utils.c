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
	while (shell->env[i] != NULL)
	{
		new_env[i] = shell->env[i];
		i++;
	}
	if (z + valid == 0)
		printf("\n");
	new_env[z + valid] = shell->env[z];
	return (i);
}

void	ft_add_new_vars(t_shell *shell, t_cmd *tmp_cmd, char **new_env)
{
	int		z;
	int		position;
	int		i;
	char	*valid;

	z = 1;
	i = 0;
	while (tmp_cmd->sim_cmd[z])
	{
		valid = ft_strdup(tmp_cmd->sim_cmd[z]);
		if (!valid)
			ft_clean(shell, 1);
		position = ft_check_env_item(shell, tmp_cmd->sim_cmd[z], &i);
		if (position < 0)
			new_env[i + z - 1] = valid;
		else
		{
			new_env[position] = valid;
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

void	ft_export_var(t_shell *shell, t_cmd *tmp_cmd, int *indexes)
{
	char	**new_env;

	g_status = 0;
	indexes[2] = 0;
	indexes[3] = 0;
	new_env = (char **) malloc (sizeof(char *) * (indexes[0] + 1 + indexes[1]));
	if (!new_env)
		ft_clean(shell, 1);
	indexes[2] = ft_transf_vars(shell, new_env, indexes[1], indexes[0]);
	ft_add_new_vars(shell, tmp_cmd, new_env);
	free(shell->env);
	shell->env = new_env;
}
