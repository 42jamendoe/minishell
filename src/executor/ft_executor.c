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
	int	end;

	end = 0;
	if (ft_handle_left_side(shell, tmp_cmd, tmp_pipe))
		end = 1;
	if (ft_handle_right_side(shell, tmp_cmd, tmp_pipe, backup) && !end)
		end = 1;
	if (ft_run_command(shell, tmp_cmd) && !end)
		end = 1;
	if (end)
	{
		g_status = 1;
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

int	ft_finish_executor(t_shell *shell, t_cmd *tmp_cmd, int backup[2], int reset)
{
	close(STDIN_FILENO);
	if (dup2(backup[0], STDIN_FILENO) < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("error: memmory aloocation", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close(backup[0]);
	if ((tmp_cmd->order_id && tmp_cmd->order_id == \
	shell->cmd_nbr - 1 && tmp_cmd->out) || reset)
	{
		close(STDOUT_FILENO);
		if (dup2(backup[1], STDOUT_FILENO) < 0)
		{
			close(backup[0]);
			ft_clean_prompt(shell);
			ft_putendl_fd("error: memmory aloocation", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		close(backup[1]);
	}
	return (EXIT_SUCCESS);
}

int	ft_executor(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	int		backup[2];
	int		tmp_pipe[2];
	int		status;

	status = 0;
	tmp_cmd = shell->command_list;
	if (ft_prepare_executor(shell, backup))
		return (EXIT_FAILURE);
	else
	{
		while (tmp_cmd)
		{
			if (ft_run_executor(shell, tmp_cmd, tmp_pipe, backup))
			{
				if (!WTERMSIG(status))
					g_status = status >> 8;
				ft_finish_executor(shell, tmp_cmd, backup, 1);
				return (EXIT_FAILURE);
			}
			if (!tmp_cmd->next)
				break ;
			tmp_cmd = tmp_cmd->next;
		}
	}
//	waitpid(-1, &status, 0);
	ft_finish_executor(shell, tmp_cmd, backup, 0);
	int zen = 0;
	while (zen > shell->cmd_nbr) {
    int status;
    pid_t child_pid = waitpid(-1, &status, 0);

    if (child_pid > 0) {
        // Processo filho com PID child_pid terminou
        zen++;
    } else if (child_pid == -1) {
        // Tratar erro ao esperar por processos filhos
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
}
	if (!WTERMSIG(status))
		g_status = status;
	return (EXIT_SUCCESS);
}
