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
#include "../includes/minishell.h"

extern long long	g_status;

int	ft_handle_left_side(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2])
{
	int	bad;

	bad = 0;
	if (tmp_cmd->in)
	{
		tmp_pipe[0] = ft_check_redir_in(tmp_cmd);
		if (dup2(tmp_pipe[0], STDIN_FILENO) < 0 || bad)
			bad = ft_exit_mem_error(shell, 0);
		close(tmp_pipe[0]);
	}
	else
	{
		if ((!tmp_cmd->order_id || !tmp_cmd->prev_has_redirout) && !bad)
			bad = ft_handle_middle_in_left_side(shell, tmp_cmd, \
			tmp_pipe);
		else if (tmp_cmd->prev_has_redirout && !bad)
			bad = ft_handle_middle_left_side(shell, tmp_pipe, backup);
	}
	return (bad);
}

int	ft_handle_middle_in_left_side(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2])
{
	int	bad;

	bad = 0;
	if (!tmp_cmd->order_id)
		tmp_pipe[0] = STDIN_FILENO;
	else
	{
		if (dup2(tmp_pipe[0], STDIN_FILENO) < 0 || bad)
			bad = ft_exit_mem_error(shell, 0);
		if (!bad)
			close(tmp_pipe[0]);
		if (pipe(tmp_pipe) < 0 || bad)
			bad = ft_exit_mem_error(shell, 1);
		if (!bad)
			close(tmp_pipe[1]);
	}
	return (bad);
}

int	ft_handle_middle_left_side(t_shell *shell, int tmp_pipe[2], int backup[2])
{
	int	bad;

	bad = 0;
	if (dup2(backup[0], tmp_pipe[0]) < 0 || bad)
		bad = ft_exit_mem_error(shell, 0);
	if (dup2(tmp_pipe[0], STDIN_FILENO) < 0 || bad)
		bad = ft_exit_mem_error(shell, 0);
	if (!bad)
		close(tmp_pipe[0]);
	return (bad);
}

int	ft_handle_middle_right_side(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2])
{
	int	bad;

	bad = 0;
	if (tmp_cmd->order_id == shell->cmd_nbr - 1)
	{
		tmp_pipe[1] = STDOUT_FILENO;
		if (tmp_cmd->out)
			tmp_pipe[1] = ft_check_redir_out(tmp_cmd);
		else
		{
			if (dup2(backup[1], tmp_pipe[1]) < 0 || bad)
				bad = ft_exit_mem_error(shell, 0);
		}
		if (dup2(tmp_pipe[1], STDOUT_FILENO) < 0 || bad)
			bad = ft_exit_mem_error(shell, 0);
	}
	return (bad);
}

int	ft_handle_right_side(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2])
{
	int	bad;

	bad = 0;
	if (tmp_cmd->order_id != (shell->cmd_nbr - 1))
	{
		if (tmp_cmd->next->in)
			tmp_pipe[1] = tmp_pipe[1];
		else
		{
			if (tmp_cmd->out)
				tmp_pipe[1] = ft_check_redir_out(tmp_cmd);
			else
			{
				if (pipe(tmp_pipe) < 0 || bad)
					bad = ft_exit_mem_error(shell, 1);
			}
		}
		if (dup2(tmp_pipe[1], STDOUT_FILENO) < 0 || bad)
			bad = ft_exit_mem_error(shell, 0);
		if (!bad)
			close(tmp_pipe[1]);
	}
	return (bad);
}
