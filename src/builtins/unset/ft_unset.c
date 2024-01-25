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

char	**ft_build_new_env(t_shell *shell, char **env, int j)
{
	int		k;
	char	**new_env;

	k = ft_list_lenght(shell);
	new_env = (char **) malloc (sizeof(char *) * (k + 1 - j));
	if (!new_env)
		ft_clean(shell, 1);
	new_env[k - j] = env[k];
	ft_loop_list(shell->env, env, new_env);
	return (new_env);
}

int	ft_validate_name(char *arg)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	if (ft_isdigit(arg[0]) || ft_strlen(arg) < 1)
		status = 1;
	while (i < (int)ft_strlen(arg) && status == 0)
	{
		if (ft_isvalidname(arg[i]) < 0)
			status = 1;
		i++;
	}
	if (status == 1)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
		arg[0] = '\0';
		return (0);
	}
	return (1);
}

int	ft_validate_arg_unset(char **env)
{
	int	i;

	i = 1;
	while (env[i])
	{
		if (ft_validate_name(env[i]) == 0)
			return (i - 1);
		i++;
	}
	return (i - 1);
}

int	ft_unset(t_shell *shell, t_cmd *tmp_cmd)
{
	char	**new_env;
	int		valid_arg;

	if (!tmp_cmd->sim_cmd[1])
		return (EXIT_SUCCESS);
	else
	{
		if (!ft_validate_arg_unset(tmp_cmd->sim_cmd))
			return (EXIT_SUCCESS);
		valid_arg = ft_check_list(shell, tmp_cmd->sim_cmd);
		if (valid_arg == 0)
			return (EXIT_SUCCESS);
		new_env = ft_build_new_env(shell, tmp_cmd->sim_cmd, valid_arg);
		free(shell->env);
		shell->env = new_env;
	}
	return (EXIT_SUCCESS);
}
