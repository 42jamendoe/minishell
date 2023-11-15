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

extern long long g_status;

void	ft_get_exit_arg(t_cmd *tmp_cmd)
{
	int	i;

	i = 0;
	while (tmp_cmd->sim_cmd[1][i])
	{
		if (!ft_isdigit(tmp_cmd->sim_cmd[1][i]))
		{
			if (tmp_cmd->sim_cmd[1][0] != '-' || tmp_cmd->sim_cmd[1][0] != '+')
			{
				ft_putstr_fd("exit:", STDOUT_FILENO);
				ft_putstr_fd(tmp_cmd->sim_cmd[1], STDOUT_FILENO);
				ft_putendl_fd(": numeric argument required", STDOUT_FILENO);
				g_status = 2;
			}
		}
		i++;
	}
}

void	ft_exit(t_shell *shell, t_cmd *tmp_cmd)
{
	int	i;
	int	status;

	i = ft_list_lenght(shell);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (i == 2)
	{
		ft_get_exit_arg(tmp_cmd);
		status = ft_atoll(tmp_cmd->sim_cmd[1]);
	}
	else if (i > 2)
	{
		status = EXIT_FAILURE;
		ft_putendl_fd(" exit: too many arguments\n", STDERR_FILENO);
	}
	else
		status = EXIT_SUCCESS;
	exit(status);
}
