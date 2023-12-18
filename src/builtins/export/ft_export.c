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
		if (!ft_isvalidname(arg[i]))
			status = 1;
		i++;
	}
	if (status == 1)
	{
		g_status = 1;
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
		arg[0] = '\0';
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	**ft_prepare_env_arg(char **env)
{
	char		*arg_eq;
	int			j;

	j = 1;
	while (env[j])
	{
		if (ft_position_of_equal(env[j]) < 0)
		{
			arg_eq = ft_strjoin(env[j], "=");
			if (!arg_eq)
				arg_eq = NULL;
			free(env[j]);
			env[j] = arg_eq;
		}
		j++;
	}
	return (env);
}

int	ft_validate_arg_export(char **env)
{
	int	i;

	i = 1;
	while (env[i])
	{
		if (ft_first_digit(env[i]))
			return (-1);
		i++;
	}
	return (i - 1);
}

int	ft_export(t_shell *shell, t_cmd *tmp_cmd)
{
	int		indexes[4];

	if (!tmp_cmd->sim_cmd[1])
		g_status = ft_env_with_declare(shell);
	else
	{
		tmp_cmd->sim_cmd = ft_prepare_env_arg(tmp_cmd->sim_cmd);
		indexes[0] = ft_list_lenght(shell);
		indexes[1] = ft_validate_arg_export(tmp_cmd->sim_cmd);
		if (indexes[1] < 0)
			return (EXIT_FAILURE);
		else
			ft_export_var(shell, tmp_cmd, indexes);
	}
	return (EXIT_SUCCESS);
}
