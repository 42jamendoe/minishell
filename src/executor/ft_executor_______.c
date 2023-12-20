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

int	ft_executor(t_shell *shell)
{
	t_cmd *cmd;
	int fdpipe[2];
	int input;
	int ret = 0;
	int output;

	cmd = shell->command_list;

	int tmpin = dup(STDIN_FILENO);
	int tmpout = dup(STDOUT_FILENO);
	if (cmd->in)
		input = ft_check_redir_in(cmd);
	else
		input = dup(tmpin);
	while (cmd)
	{
		dup2(input, STDIN_FILENO);
		close(input);
		if (cmd->order_id == shell->cmd_nbr - 1)
		{
			if(cmd->out)
				output = ft_check_redir_out(cmd); 
			else
				output = dup(tmpout);
		}
		else
		{
			pipe(fdpipe);
			output = fdpipe[1];
			input = fdpipe[0];
		}
		dup2(output,STDOUT_FILENO);
		close(output);
		ret = fork();
		if(ret == 0)
			ft_execute_cmd(shell, cmd);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
		//if (cmd->order_id)
		close(STDIN_FILENO);
		if (cmd->order_id != shell->cmd_nbr - 1)
			close(STDOUT_FILENO);
		else
			close(fdpipe[1]);	
	}
	dup2(tmpin,STDIN_FILENO);
	if (cmd->order_id != shell->cmd_nbr - 1)
		dup2(tmpout,STDOUT_FILENO);
	close(tmpin);
	close(tmpout);
	waitpid(-1, NULL, 0);
	return (EXIT_SUCCESS);
}