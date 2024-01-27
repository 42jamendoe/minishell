/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void	ft_execute_cmd(t_shell *shell, t_cmd *tmp_cmd)
{
	char	*binpath;

	binpath = ft_search_cmd(shell, tmp_cmd);
	if (binpath)
	{
		if (execve(binpath, tmp_cmd->sim_cmd, shell->env) < 0)
		{
			ft_print_error(5);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			exit(127);
		}
	}
	else
	{
		if (tmp_cmd->order_id > 0 || tmp_cmd->in)
			close(STDIN_FILENO);
		if (tmp_cmd->order_id != shell->cmd_nbr - 1 || tmp_cmd->out)
			close(STDOUT_FILENO);
		if (shell->cmd_nbr == 1)
			ft_putendl_fd("minishel: command not found", STDERR_FILENO);
		exit(127);
	}
}
