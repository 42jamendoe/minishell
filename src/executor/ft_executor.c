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

int ft_fork_(t_shell *shell, t_cmd *cmd, int pipe_fd[2], int backup[2])
{
	cmd->pid_cmd = fork();
	if (cmd->pid_cmd == 0)
	{
		close(pipe_fd[1]);
		close(backup[0]);
		close(backup[1]);
		ft_execute_cmd(shell, cmd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

int ft_handle_right_side_(t_shell *shell, t_cmd *cmd, int pipe_fd[2], int backup[2])
{
	(void) cmd;
	if (cmd->next && pipe(pipe_fd) < 0)
	{
		ft_clean_prompt(shell);
		return (EXIT_FAILURE);
	}
	if (cmd->out)
		pipe_fd[1]  = ft_check_redir_out(cmd, pipe_fd);
	else if (!cmd->next)
		pipe_fd[1] = dup(backup[1]);
	close(STDOUT_FILENO);
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("minishell: pipe_ft[1]: bad file descriptor", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close(pipe_fd[1]);
	return (EXIT_SUCCESS);
}

t_cmd *ft_handle_left_side_(t_shell *shell, t_cmd *cmd, int pipe_fd[2])
{
	(void) shell;
	while (input < 0)
	{
		if (cmd->in)
			input = ft_check_redir_in(cmd);
		else
		{
			input = dup(STDIN_FILENO);
			if (input < 0)
			ft_putendl_fd("minishell: input: bad file descriptor", STDERR_FILENO);
		}
		if (input < 0 && cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	close(STDIN_FILENO);
	if (dup2(input, STDIN_FILENO) < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("minishell: input: bad file descriptor", STDERR_FILENO);
		return (NULL);
	}
	close (input);
	return (cmd);
}

int ft_prepare_executor_(t_shell *shell, int backup[2])
{
	backup[0] = dup(STDIN_FILENO);
	if (backup[0] < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("minishell: backup[0]: bad file descriptor", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	backup[1] = dup(STDOUT_FILENO);
	if (backup[1] < 0)
	{
		close(backup[0]);
		ft_clean_prompt(shell);
		ft_putendl_fd("minishell: backup[1]: bad file descriptor", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int ft_run_executor_(t_shell *shell, t_cmd *cmd, int pipe_fd[2])
{
	int	backup[2];

	if (ft_prepare_executor_(shell, backup))
		return (EXIT_FAILURE);
	//ft_handle_left_side_(shell, cmd, input);
	ft_handle_right_side_(shell, cmd, pipe_fd, backup);
	ft_fork_(shell, cmd, pipe_fd, backup);
	return (EXIT_SUCCESS);
}

int ft_executor(t_shell *shell)
{
	t_cmd *cmd;
	int	pipe_fd[2];

	cmd = shell->command_list;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	while (cmd)
	{
		cmd = ft_handle_left_side_(shell, cmd, pipe_fd);
		if (!cmd)
			break ;
		if (ft_run_executor_(shell, cmd, pipe_fd))
			return (EXIT_FAILURE);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	cmd = shell->command_list;
	waitpid(-1, NULL, 0);
	return (EXIT_SUCCESS);
}
