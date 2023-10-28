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

void ft_change_env_path(t_shell *shell, char *newd, char *path)
{
	int i;

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

int	ft_cd(t_shell *shell, char **newd)
{	
	char		path[PATH_MAX];
	char		*directory;
	
	getcwd(path, PATH_MAX);
	directory = NULL;
 	if (!newd[1] || !ft_strncmp(newd[1], "~", 2))
		directory = getenv("HOME");
	else if (!ft_strncmp(newd[1], "-", 2))
		directory = getenv("OLDPWD");
	if (directory)
	{
		if (chdir(directory))
		{
			ft_putstr_fd(directory, STDERR_FILENO);
			ft_putstr_fd(": not defined", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	else
		directory = newd[1];
	if (chdir(directory))
	{
		ft_putstr_fd(directory, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
		ft_change_env_path(shell, directory, path);
	return (EXIT_SUCCESS);
}


/* if cd or cd ~ the diretory must change to HOME and if cd - the diretory must change to OLDPWD*/