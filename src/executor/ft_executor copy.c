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

int	ft_exec_utor(t_shell *shell)
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
	waitpid(-1, &status, 0);
	ft_finish_executor(shell, tmp_cmd, backup, 0);
	if (!WTERMSIG(status))
		g_status = status >> 8;
	return (EXIT_SUCCESS);
}

int ft_executor(t_shell *shell)
{
	int tmpin = dup(STDIN_FILENO);
	int tmpout = dup(STDOUT_FILENO);
	int pipefd[2];
	int input;
	int i;

	i = 0;
	t_cmd *cmd = shell->command_list;

	if (cmd->in)
		input = ft_check_redir_in;
	else
		input = dup(tmpin);
	
	int ret;
	int output;
	while (i < shell->cmd_nbr)
	{
		if (cmd->out)
			output = ft_check_redir_out;
		else
		{
			if (i == shell->cmd_nbr - 1)
				output = dup(tmpout);
			else
				pipe(pipefd);
			output = pipefd[1];
			input = pipefd[0];
		}
		dup2(output, STDOUT_FILENO);
		close(output);
		ret = fork();
		if (ret == 0)
		{
			ft_run_command(shell, cmd);
		}
	}
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
	waitpid(ret, &g_status, 0);
	i++;
}