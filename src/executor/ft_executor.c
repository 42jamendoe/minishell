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


int ft_finish_executor_(t_shell *shell, int backup[2])
{

	if (dup2(backup[0], STDIN_FILENO) < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("minishell: backup[0]: bad file descriptor", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close(backup[0]);
	if (dup2(backup[1], STDOUT_FILENO) < 0)
	{
		close(backup[1]);
		ft_clean_prompt(shell);
		ft_putendl_fd("minishell: backup[1]: bad file descriptor", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close(backup[1]);
	return (EXIT_SUCCESS);
}


int ft_fork_(t_shell *shell, t_cmd *cmd, int pipe_fd[2], int backup[2])
{
	// int input;

	// input = 0;
	cmd->pid_cmd = fork();
	if (cmd->pid_cmd == 0)
	{
		//if (shell->cmd_nbr > 1 && cmd->order_id > 0 && cmd->order_id < shell->cmd_nbr - 1)
			close(pipe_fd[0]);
		close(backup[0]);
		close(backup[1]);
		ft_execute_cmd(shell, cmd);
		return (EXIT_SUCCESS);
	}
	//if (cmd->order_id != shell->cmd_nbr -1)
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);		
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
	while (1)
	{
		if (cmd->in)
			pipe_fd[0] = ft_check_redir_in(cmd);
		else
		{
			if (cmd->order_id == 0)
				pipe_fd[0] = dup(STDIN_FILENO);
			if (pipe_fd[0] < 0)
				ft_putendl_fd("minishell: pipe_fd[0]: bad file descriptor", STDERR_FILENO);
		}
		if (pipe_fd[0] < 0 && cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	int input;
	input = dup(pipe_fd[0]);
	close (pipe_fd[0]);
	close(STDIN_FILENO);
	if (dup2(input, STDIN_FILENO) < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("minishell: pipe_fd[0]: bad file descriptor", STDERR_FILENO);
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

	if (shell->command_list->function_name > 0 && \
	!shell->command_list->redir && shell->cmd_nbr == 1)
	{
		ft_run_builtin(shell, cmd);
	}
	else
	{
	if (ft_prepare_executor_(shell, backup))
		return (EXIT_FAILURE);
	ft_handle_left_side_(shell, cmd, pipe_fd);
	ft_handle_right_side_(shell, cmd, pipe_fd, backup);
	ft_fork_(shell, cmd, pipe_fd, backup);
	if (ft_finish_executor_(shell, backup))
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int ft_executor(t_shell *shell)
{
	t_cmd *cmd;
	int status;
	int	pipe_fd[2];

	cmd = shell->command_list;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	while (cmd)
	{	
		if (ft_run_executor_(shell, cmd, pipe_fd))
			return (EXIT_FAILURE);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	cmd = shell->command_list;
	if (!(shell->command_list->function_name > 0 && \
	!shell->command_list->redir && shell->cmd_nbr == 1))
	{
		waitpid(-1, &status, 0);
		g_status = WEXITSTATUS(status);
	}
	return (EXIT_SUCCESS);
}
