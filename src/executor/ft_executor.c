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
#include "../../includes/minishell.h"

int	ft_run_builtin(t_shell *shell, t_cmd *tmp_cmd)
{
	if (tmp_cmd->function_name == 1)
		g_status = ft_echo(tmp_cmd);
	else if (tmp_cmd->function_name == 2)
		g_status = ft_cd(shell, tmp_cmd);
	else if (tmp_cmd->function_name == 3)
		g_status = ft_pwd();
	else if (tmp_cmd->function_name == 4)
		g_status = ft_export(shell, tmp_cmd);
	else if (tmp_cmd->function_name == 5)
		g_status = ft_unset(shell, tmp_cmd);
	else if (tmp_cmd->function_name == 6)
		g_status = ft_env(shell);
	else if (tmp_cmd->function_name == 7)
		ft_exit(shell, tmp_cmd);
	else
		return (-1);
	return (g_status);
}

int	ft_run_other(t_shell *shell, t_cmd *cmd, int pipe_fd[2], int input)
{
	if (pipe(pipe_fd) < 0)
	{
		ft_clean_prompt(shell);
		return (EXIT_FAILURE);
	}
	cmd->pid_cmd = fork();
	if (cmd->pid_cmd == 0)
	{
		signal(SIGINT, fork_child);
		if (cmd->order_id != shell->cmd_nbr - 1)
			ft_not_last_command(shell, pipe_fd);
		if (cmd->order_id > 0)
			ft_after_first_command(shell, pipe_fd, input);
		ft_handle_exec_red(shell, cmd, pipe_fd);
	}
	else
		input = ft_after_fork(shell, cmd, pipe_fd, input);
	return (input);
}

int	ft_executor(t_shell *shell)
{
	t_cmd	*cmd;
	int		input;
	int		pipe_fd[2];

	input = STDIN_FILENO;
	cmd = shell->command_list;
	while (cmd)
	{
		if (shell->cmd_nbr == 1 && cmd->function_name > 0 && !cmd->redir)
			ft_run_builtin(shell, cmd);
		else
			input = ft_run_other(shell, cmd, pipe_fd, input);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	ft_finish_executor_new(shell);
	return (EXIT_SUCCESS);
}
