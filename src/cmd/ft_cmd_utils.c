/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

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
			free(paths_char);
			return (splited);
		}
	}
	return (NULL);
}

char	*ft_get_net_path(char **paths, char *binpath, int *i)
{
	if (access(binpath, F_OK | X_OK) != 0)
	{
		free(binpath);
		(*i)++;
	}
	else
	{
		(*i)++;
		while (paths[(*i)])
			free(paths[(*i)++]);
		free(paths);
		return (binpath);
	}
	return (NULL);
}

char	*get_sys_binpath(t_shell *shell, t_cmd *tmp_cmd)
{
	int		i;
	char	*binpath;
	char	*tmp;
	char	**paths;

	i = 0;
	binpath = NULL;
	tmp = NULL;
	paths = ft_get_paths(shell);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		if (!tmp)
			ft_clean(shell, 1);
		binpath = ft_strjoin(tmp, tmp_cmd->sim_cmd[0]);
		free(tmp);
		if (!binpath)
			ft_clean(shell, 1);
		binpath = ft_get_net_path(paths, binpath, &i);
		if (binpath)
			return (binpath);
	}
	free(paths);
	return (NULL);
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
