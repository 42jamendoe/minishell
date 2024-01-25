/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"

void	ft_change_env_path(t_shell *shell, char *newd, char *path)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "PWD=", 4) || \
		!ft_strncmp(shell->env[i], "OLDPWD=", 7))
		{
			free(shell->env[i]);
			if (!ft_strncmp(shell->env[i], "PWD=", 4))
				shell->env[i] = ft_strjoin("PWD=", newd);
			else
				shell->env[i] = ft_strjoin("OLDPWD=", path);
		}
		i++;
	}
}

void	ft_print_error_cd(char *directory)
{
	if (!directory)
	{
		ft_putstr_fd(directory, STDERR_FILENO);
		ft_putstr_fd(": not defined", STDERR_FILENO);
	}
	if (chdir(directory))
	{
		ft_putstr_fd(directory, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
}

int	ft_count_arg_sim_cmd(char **args)
{
	int	i;

	i = 1;
	if (args[i])
	{
		while (args[i])
			i++;
		return (i - 1);
	}
	else
		return (0);
}

char	*ft_new_check_dir(t_cmd *tmp_cmd)
{
	char	*directory;

	directory = NULL;
	if (!tmp_cmd->sim_cmd[1] || !ft_strncmp(tmp_cmd->sim_cmd[1], "~", 2))
		directory = getenv("HOME");
	else if (!ft_strncmp(tmp_cmd->sim_cmd[1], "-", 2))
		directory = getenv("OLDPWD");
	else
		directory = tmp_cmd->sim_cmd[1];
	return (directory);
}

int	ft_cd(t_shell *shell, t_cmd *tmp_cmd)
{
	char		path[PATH_MAX];
	char		*directory;

	if (ft_count_arg_sim_cmd(tmp_cmd->sim_cmd) > 1)
	{
		g_status = 1;
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!getcwd(path, PATH_MAX))
		return (EXIT_FAILURE);
	directory = ft_new_check_dir(tmp_cmd);
	if (!directory || chdir(directory))
	{
		g_status = 1;
		ft_print_error_cd(directory);
		return (EXIT_FAILURE);
	}
	ft_change_env_path(shell, directory, path);
	return (EXIT_SUCCESS);
}

/* if cd or cd ~ the diretory must change to HOME and if cd - 
the diretory must change to OLDPWD*/