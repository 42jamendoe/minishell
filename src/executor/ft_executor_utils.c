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
