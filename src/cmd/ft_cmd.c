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

extern long long	g_status;

char	*get_sys_binpath(t_shell *shell, t_cmd *tmp_cmd)
{
	int		i;
	char	*binpath;
	char	**paths;

	i = 0;
	binpath = NULL;
	paths = ft_get_paths(shell);
	while (paths[i])
	{
		binpath = ft_strjoin(ft_strjoin(paths[i], "/"), \
			tmp_cmd->sim_cmd[0]);
		if (!binpath)
			ft_clean(shell, 1);
		if (access(binpath, F_OK) != 0)
		{
			free(binpath);
			i++;
		}
		else
			break ;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	return (binpath);
}

char	*ft_search_cmd(t_shell *shell, t_cmd *tmp_cmd)
{
	char	*binpath;

	if (tmp_cmd->sim_cmd[0][0] == '/')
		binpath = tmp_cmd->sim_cmd[0];
	else
	{
		binpath = get_sys_binpath(shell, tmp_cmd);
		if (!binpath)
		{
			printf("Command not found\n");
			g_status = 127;
			return (NULL);
		}
	}
	return (binpath);
}

void	ft_run_cmd_lib(t_shell *shell)
{
	t_cmd	*tmp;
	char	*new;
	char	**path;
	int		i;

	path = ft_get_paths(shell);
	tmp = shell->command_list;
	while (tmp)
	{
		i = 0;
		while (path[i])
		{
			if (access(ft_strjoin(ft_strjoin(path[i], "/"), \
			tmp->sim_cmd[0]), F_OK) != 0)
				i++;
			else
				break ;
		}
		new = ft_strjoin(ft_strjoin(path[i], "/"), tmp->sim_cmd[0]);
		free(tmp->sim_cmd[0]);
		tmp->sim_cmd[0] = new;
		tmp = tmp->next;
	}
}

void	ft_execute_cmd(t_shell *shell, t_cmd *tmp_cmd)
{
	char	*binpath;

	binpath = ft_search_cmd(shell, tmp_cmd);
	if (binpath)
	{
		if (execve(binpath, tmp_cmd->sim_cmd, shell->env) < 0)
		{
			ft_print_error(5);
			exit(127);
		}
	}
}
