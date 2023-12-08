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

int	ft_run_executor(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2])
{
	if (ft_handle_left_side(shell, tmp_cmd, tmp_pipe, backup))
	{
		g_status = 1;
		return (EXIT_FAILURE);
	}
	if (ft_handle_middle_right_side(shell, tmp_cmd, tmp_pipe, backup))
	{
		g_status = 1;
		return (EXIT_FAILURE);
	}
	if (ft_handle_right_side(shell, tmp_cmd, tmp_pipe))
	{
		g_status = 1;
		return (EXIT_FAILURE);
	}
	if (ft_run_command(shell, tmp_cmd))
	{
		g_status = 1;
		return (EXIT_FAILURE);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (dup2(backup[0], STDIN_FILENO) < 0)
	{
		g_status = 1;
		ft_clean_prompt(shell);
		ft_putendl_fd("error getting command", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (dup2(backup[1], STDOUT_FILENO) < 0)
	{
		g_status = 1;
		ft_clean_prompt(shell);
		ft_putendl_fd("error getting command", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (g_status);
}

int	ft_prepare_executor(t_shell *shell, int backup[2])
	{
	backup[0] = dup(STDIN_FILENO);
	if (backup[0] < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("error: memmory aloocation", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	backup[1] = dup(STDOUT_FILENO);
	if (backup[1] < 0)
	{
		close(backup[0]);
		ft_clean_prompt(shell);
		ft_putendl_fd("error: memmory aloocation", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_finish_executor(t_shell *shell, int backup[2])
{
	if (dup2(backup[0], STDIN_FILENO) < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("error: memmory aloocation", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (dup2(backup[1], STDOUT_FILENO) < 0)
	{
		close(backup[0]);
		ft_clean_prompt(shell);
		ft_putendl_fd("error: memmory aloocation", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_executor(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	int		backup[2];
	int		tmp_pipe[2];
	int		status;
	pid_t	child_pid;

	status = 0;
	tmp_cmd = shell->command_list;
	if (ft_prepare_executor(shell, backup))
		return (EXIT_FAILURE);
	while (tmp_cmd)
	{
		if (ft_run_executor(shell, tmp_cmd, tmp_pipe, backup))
		{
			ft_finish_executor(shell, backup);
			return (EXIT_FAILURE);
		}
		if (!tmp_cmd->next)
			break ;
		tmp_cmd = tmp_cmd->next;
	}
	while ((child_pid = waitpid(-1, &status, 0)) > 0)
	{
        //printf("Child process %d exited with status %d\n", child_pid, status);
    }
	if (!WTERMSIG(status))
		g_status = status >> 8;
	if (ft_finish_executor(shell, backup))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
