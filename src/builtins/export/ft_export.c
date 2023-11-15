/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"

extern long long	g_status;

int	ft_check_env_item(t_shell *shell, char *arg, int *i)
{
	int	position;

	position = ft_position_of_equal(arg);
	(*i) = 1;
	while (shell->env[(*i)])
	{
		if (!ft_strncmp(shell->env[(*i)], arg, position))
			return (*i);
		(*i)++;
	}
	return (-1);
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

int	ft_first_digit(char *arg)
{
	int		i;
	int		position;
	int		status;

	i = 0;
	status = 0;
	position = ft_position_of_equal(arg);
	if (ft_isdigit(arg[0]) || position < 1)
		status = 1;
	while (i < position && status == 0)
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

int	ft_validate_arg_export(char **env)
{
	int	i;

	i = 1;
	while (env[i])
	{
		if (ft_first_digit(env[i]) == 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (i - 1);
}

int	ft_export(t_shell *shell, t_cmd *tmp_cmd)
{
	int		indexes[4];
	char	**new_env;

	if (!tmp_cmd->sim_cmd[1])
		g_status = ft_env_with_declare(shell);
	else
	{
		indexes[0] = ft_list_lenght(shell);
		indexes[1] = ft_validate_arg_export(tmp_cmd->sim_cmd);
		indexes[2] = 0;
		indexes[3] = 0;
		new_env = (char **) malloc (sizeof(char *) * (indexes[0] + indexes[1]));
		if (!new_env)
			ft_clean(shell, 1);
		indexes[2] = ft_transf_vars(shell, new_env, indexes[1], indexes[0]);
		ft_add_new_vars(shell, tmp_cmd, new_env);
		free(shell->env);
		shell->env = new_env;
	}
	return (g_status);
}
