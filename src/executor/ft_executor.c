/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

extern long long	g_status;

int	ft_run_executor(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2])
{
	int	bad;

	bad = ft_handle_left_side(shell, tmp_cmd, tmp_pipe, backup);
	if (!bad)
		bad = ft_handle_middle_right_side(shell, tmp_cmd, tmp_pipe, backup);
	if (!bad)
		bad = ft_handle_right_side(shell, tmp_cmd, tmp_pipe);
	if (!bad)
		ft_run_command(shell, tmp_cmd);
	if (!bad)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	if (dup2(backup[0], STDIN_FILENO) < 0 || bad)
		bad = ft_exit_mem_error(shell, 0);
	if (dup2(backup[1], STDOUT_FILENO) < 0 || bad)
		bad = ft_exit_mem_error(shell, 0);
	return (bad);
}

int	ft_prepare_executor(t_shell *shell, int backup[2])
{
	int	bad;

	bad = 0;
	backup[0] = dup(STDIN_FILENO);
	if (backup[0] < 0 || bad)
		bad = ft_exit_mem_error(shell, 0);
	if (!bad)
		backup[1] = dup(STDOUT_FILENO);
	if (backup[1] < 0 || bad)
		bad = ft_exit_mem_error(shell, 0);
	return (bad);
}

int	ft_finish_executor(t_shell *shell, int backup[2])
{
	int	bad;

	bad = 0;
	if (dup2(backup[0], STDIN_FILENO) < 0 || bad)
		bad = ft_exit_mem_error(shell, 0);
	if (!bad)
		close(backup[0]);
	if (dup2(backup[1], STDOUT_FILENO) < 0 || bad)
		bad = ft_exit_mem_error(shell, 0);
	if (!bad)
		close(backup[1]);
	return (bad);
}

void	ft_executor(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	int		backup[2];
	int		tmp_pipe[2];
	int		bad;

	bad = 0;
	tmp_cmd = shell->command_list;
	bad = ft_prepare_executor(shell, backup);
	while (tmp_cmd && !bad)
	{
		bad = ft_run_executor(shell, tmp_cmd, tmp_pipe, backup);
		if (!tmp_cmd->next || bad)
			break ;
		tmp_cmd = tmp_cmd->next;
	}
	if (!bad)
		ft_finish_executor(shell, backup);
}
