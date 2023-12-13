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

int	ft_handle_left_side(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2])
{
	if (tmp_cmd->in)
	{
		tmp_pipe[0] = ft_check_redir_in(tmp_cmd);
		if (tmp_pipe[0] == -1)
		{
			if (tmp_cmd->order_id)
				close(tmp_pipe[1]);
			ft_clean_prompt(shell);
			return (EXIT_FAILURE);
		}
		else if (dup2(tmp_pipe[0], STDIN_FILENO) < 0)
		{
			if (tmp_cmd->order_id)
				close(tmp_pipe[1]);
			ft_clean_prompt(shell);
			return (EXIT_FAILURE);
		}
		close(tmp_pipe[0]);
	}
	else
		if (ft_handle_left_side_noredir(shell, tmp_cmd, \
tmp_pipe, backup))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_handle_middle_in_left_side(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2])
{
	if (!tmp_cmd->in)
	{
		if (!tmp_cmd->order_id)
			tmp_pipe[0] = STDIN_FILENO;
		else
		{
			if (dup2(tmp_pipe[0], STDIN_FILENO) < 0)
			{
				ft_clean_prompt(shell);
				return (EXIT_FAILURE);
			}
			close(tmp_pipe[0]);
			if (pipe(tmp_pipe) < 0)
			{
				ft_clean_prompt(shell);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_handle_middle_left_side(t_shell *shell, t_cmd *tmp_cmd, int tmp_pipe[2], int backup[2])
{
	if (!tmp_cmd->in)
	{
		if (dup2(backup[0], tmp_pipe[0]) < 0)
		{
			ft_clean_prompt(shell);
			return (EXIT_FAILURE);
		}
		if (dup2(tmp_pipe[0], STDIN_FILENO) < 0)
		{
			ft_clean_prompt(shell);
			return (EXIT_FAILURE);
		}
		close(tmp_pipe[0]);
	}
	return (EXIT_SUCCESS);
}

int	ft_handle_middle_right_side(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2])
{
	if (tmp_cmd->order_id == shell->cmd_nbr - 1)
	{

		if (tmp_cmd->out)
		{
			//tmp_pipe[1] = STDOUT_FILENO;
			tmp_pipe[1] = ft_check_redir_out(tmp_cmd);
			if (tmp_pipe[1] < 0)
				return (EXIT_FAILURE);
		}
		else
		{
			if (dup2(backup[1], tmp_pipe[1]) < 0)
			{
				ft_clean_prompt(shell);
				return (EXIT_FAILURE);
			}
		}
		if (dup2(tmp_pipe[1], STDOUT_FILENO) < 0)
		{
			ft_clean_prompt(shell);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_handle_right_side(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2])
{
	if (tmp_cmd->order_id != (shell->cmd_nbr - 1))
	{
		if (tmp_cmd->next->in)
			tmp_pipe[1] = tmp_pipe[1];
		else
		{
			if (tmp_cmd->out)
			{
				tmp_pipe[1] = ft_check_redir_out(tmp_cmd);
				if (tmp_pipe[1] < 0)
					return (ft_clean_prompt(shell));
			}
//			else
//			{
//				if (pipe(tmp_pipe) < 0)
//					return (ft_clean_prompt(shell));
//			}
			if (dup2(backup[1], STDOUT_FILENO) < 0)
				return (ft_clean_prompt(shell));
		}
		close(tmp_pipe[1]);
	}
	return (EXIT_SUCCESS);
}
