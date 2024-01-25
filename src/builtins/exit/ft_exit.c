/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"

int	ft_check_exit_arg(char *arg)
{
	int	i;
	int	valid;

	i = 0;
	valid = 0;
	while (arg[i] != '\0' && valid == 0)
	{
		if (!ft_isdigit(arg[i]))
		{
			valid = 1;
			if (i == 0 && (arg[0] == '-' || arg[0] == '+'))
				valid = 0;
		}
		i++;
	}
	return (valid);
}

void	ft_get_exit_arg(char *arg)
{
	if (ft_check_exit_arg(arg))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_status = 2;
	}
	else
	{
		g_status = ft_atoi(arg);
	}
}

void	ft_exit(t_shell *shell, t_cmd *tmp_cmd)
{
	int	i;

	ft_putendl_fd("exit", STDOUT_FILENO);
	i = tmp_cmd->arg_nbr - 2;
	if (i == 0)
		g_status = 0;
	else if (i == 1)
		ft_get_exit_arg(tmp_cmd->sim_cmd[1]);
	else
	{
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		g_status = EXIT_FAILURE;
	}
	ft_clean_exit(shell);
	exit(g_status);
}
