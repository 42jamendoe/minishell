/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	ft_create_pipes(t_shell *shell, int pipe_fds[][2])
{
	int i;

	i = 0;
	while (i < shell->cmd_nbr + 2)
	{
		if (pipe(pipe_fds[i]) < 0)
		{
			ft_clean();
		}
		i++;
	}
	return (0);
}

int ft_close_pipes(t_shell * shell, t_cmd *tmp_cmd, int pipe_fds[][2])
{
	int j;

	j = 0;
	while (j < shell->cmd_nbr + 1)
	{
		if (tmp_cmd->order_id != j - 1)
		{
			printf("fechou o [%d][1] no comando i=%d\n", j, tmp_cmd->order_id);
			close(pipe_fds[j][1]);
		}
		if (tmp_cmd->order_id != j)
		{
			printf("fechou o [%d][0] no comando i=%d\n", j, tmp_cmd->order_id);
			close(pipe_fds[j][0]);
		}
		j++;
	}
	return (0);
}




int	ft_run_builtin(t_shell *shell, int function)
{
	if (function == 0)
		ft_echo(shell, shell->command_list->sim_cmd);
	else if (function == 1)
		ft_cd(shell, shell->command_list->sim_cmd);
	else if (function == 2)
		ft_pwd();
	else if (function == 3)
		ft_export(shell, shell->command_list->sim_cmd);
	else if (function == 4)
		ft_unset(shell, shell->command_list->sim_cmd);
	else if (function == 5)
		ft_env(shell);
	else if (function == 6)
		ft_exit(shell, shell->command_list->sim_cmd);
	return (-1);
}