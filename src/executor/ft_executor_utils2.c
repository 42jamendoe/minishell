/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

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

char	**ft_get_paths(t_shell *shell)
{
	int		i;
	char	*paths_char;
	char	**splited;

	i = 0;
	splited = NULL;
	while (shell->env[i])
	{
		if (shell->env[i] && ft_strncmp(shell->env[i], "PATH=", 5))
			i++;
		else
		{
			paths_char = ft_substr(shell->env[i], 5, \
			ft_strlen(shell->env[i]) - 5);
			splited = ft_split(paths_char, ':');
			return (splited);
		}
	}
	return (NULL);
}

void	ft_fork(t_shell *shell, t_cmd *tmp_cmd)
{
	pid_t	cmd;

	cmd = fork();
	if (cmd < 0)
		ft_clean(shell, 1);
	if (cmd == 0)
	{
		ft_execute_cmd(shell, tmp_cmd);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exit (EXIT_SUCCESS);
	}
}

int	ft_run_command(t_shell *shell, t_cmd *tmp_cmd)
{
	if (shell->command_list->function_name > 0 && \
	!shell->command_list->redir && shell->cmd_nbr == 1)
	{
		ft_run_builtin(shell, tmp_cmd);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	else
		ft_fork(shell, tmp_cmd);
	return (EXIT_SUCCESS);
}
