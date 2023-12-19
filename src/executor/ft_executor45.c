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
	if (ft_handle_left_side(shell, tmp_cmd, tmp_pipe))
		return (EXIT_FAILURE);
	if (ft_handle_right_side(shell, tmp_cmd, tmp_pipe, backup))
		return (EXIT_FAILURE);
	if (ft_run_command(shell, tmp_cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
				ft_finish_executor(shell, tmp_cmd, backup, 1);
				return (EXIT_FAILURE);
			}
			if (!tmp_cmd->next)
				break ;
			tmp_cmd = tmp_cmd->next;
		}
		while (wait(&status) > 0)
		{
			// Processar o status de cada processo filho
			if (WIFEXITED(status))
			{
				write(STDERR_FILENO, "processo\n", sizeof("processo\n"));// Processo filho terminou normalmente
			}else
			{
				// Processo filho terminou com um erro
			}
		}
		//waitpid(-1, &status, 0);
		ft_finish_executor(shell, tmp_cmd, backup, 0);
		if (!WTERMSIG(status))
			g_status = status >> 8;
	}
	return (EXIT_SUCCESS);
}

int ft_executor(t_shell *shell);

{
	int tmpin = dup(STDIN_FILENO);
	int tmpout = dup(STDOUT_FILENO);
	int pipefd[2];
	int input = dup(tmpin);
	int output = dup(tmpout);
	int ret;

	t_cmd *cmd = shell->command_list;

	while (cmd)
	{
		if (cmd->in)
			input = ft_check_redir_in(cmd);
		else
			input = dup(tmpin);

		if (cmd->order_id)
		{
			if (cmd->out)
				output = ft_check_redir_out(cmd);
			else
				output = dup(tmpout);
		}
{
	int tmpin = dup(STDIN_FILENO);
	int tmpout = dup(STDOUT_FILENO);
	int pipefd[2];
	int input = dup(tmpin);
	int output = dup(tmpout);
	int ret;

	t_cmd *cmd = shell->command_list;

	while (cmd)
	{
		if (cmd->in)
			input = ft_check_redir_in(cmd);
		else
			input = dup(tmpin);

		if (cmd->order_id)
		{
			if (cmd->out)
				output = ft_check_redir_out(cmd);
			else
				output = dup(tmpout);
		}
		else
		{
			pipe(pipefd);
			output = pipefd[1];
			input = pipefd[0];
		}

		ret = fork();
		if (ret == 0)
		{
			dup2(input, STDIN_FILENO);
			close(input);
			dup2(output, STDOUT_FILENO);
			close(output);

			ft_run_command(shell, cmd);
			exit(0); // Exit the child process
		}
		else
		{
			close(input);
			close(output);
			waitpid(ret, &g_status, 0);
		}
		if (!cmd->next)
			break;
		cmd = cmd->next; // Move to the next command in the list
	}
	dup2(tmpin, STDIN_FILENO);
	dup2(tmpout, STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
	return (EXIT_SUCCESS);
}
