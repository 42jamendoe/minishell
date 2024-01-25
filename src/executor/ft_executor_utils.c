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
#include "../../includes/minishell.h"

void	ft_not_last_command(t_shell *shell, int pipe_fd[2])
{
	close(STDOUT_FILENO);
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("minishell: pipe_fd[1]: bad file descriptor", \
		STDERR_FILENO);
	}
	else
		close(pipe_fd[1]);
}

void	ft_after_first_command(t_shell *shell, int pipe_fd[2], int input)
{
	close(STDIN_FILENO);
	if (dup2(input, STDIN_FILENO) < 0)
	{
		ft_clean_prompt(shell);
		ft_putendl_fd("minishell: pipe_fd[0]: bad file descriptor", \
		STDERR_FILENO);
	}
	close(input);
	close(pipe_fd[0]);
}

int	ft_handle_exec_red(t_shell *shell, t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->in)
		ft_check_redir_in(cmd, pipe_fd);
	else if (cmd->order_id == 0)
		close(pipe_fd[0]);
	if (cmd->out)
		ft_check_redir_out(cmd, pipe_fd);
	else if (cmd->order_id == shell->cmd_nbr - 1)
		close(pipe_fd[1]);
	if (cmd->order_id == shell->cmd_nbr - 1 && !cmd->redir \
	&& shell->cmd_nbr > 1)
		close(pipe_fd[1]);
	ft_execute_cmd(shell, cmd);
	return (EXIT_SUCCESS);
}

int	ft_after_fork(t_shell *shell, t_cmd *cmd, int pipe_fd[2], int input)
{
	if (cmd->order_id > 0)
		close(input);
	if (cmd->order_id == shell->cmd_nbr - 1)
	{
		close(pipe_fd[0]);
	}
	else
	{
		input = dup(pipe_fd[0]);
		if (!input)
			return (-1);
		close(pipe_fd[0]);
	}
	close(pipe_fd[1]);
	return (input);
}

void	ft_finish_executor_new(t_shell *shell)
{
	int		status;
	t_cmd	*cmd;

	status = 0;
	cmd = shell->command_list;
	if (cmd->function_name < 0 || shell->command_list->redir \
	|| shell->cmd_nbr > 1)
	{
		while (cmd)
		{
			waitpid(cmd->pid_cmd, &status, 0);
			g_status = WEXITSTATUS(status);
			if (!WTERMSIG(status))
				g_status = status >> 8;
			if (!cmd->next)
				break ;
			cmd = cmd->next;
		}
	}
}
