/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int ft_check_env_item(t_shell *shell, char *arg)
{
	int position;
	int i;

	position = ft_position_of_equal(arg);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], arg, position))
			return (i);
		i++;
	}
	return (-1);
}

int ft_position_of_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_first_digit(char *arg)
{
	int i;
	int position;
	int status;

	i = 0;
	status = 0;
	position = ft_position_of_equal(arg);
	if (ft_isdigit(arg[0]) || position < 1)
		status = 1;
	while (i < position && status == 0)
	{
		if (!ft_isvalidname(arg[i]))
			status = 1;
		i++;
	}
	if (status == 1)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
		arg[0] = '\0'; 
		return (0);		
	}
	return (1);
}


int ft_validate_arg(char **env)
{
	int valid;
	int i;

	valid = 0;
	i = 0;
	while (env[i])
	{
		valid += ft_first_digit(env[i]);
		i++;
	}
	return (valid);
}


int	ft_export(t_shell *shell, char **env)
{
	int i;
	int valid;
	char **new_env;
	int z;
	int position;

	i = 0;
	z = 0;
	if (!env[1])
		ft_env(shell);
	else
	{
		while (shell->env[z])
			z++;
		valid = ft_validate_arg(env);
		new_env = (char **) malloc (sizeof(char *) * (z + valid));
		if (!new_env)
			ft_clean();
		while (shell->env[i])
		{
			new_env[i] = shell->env[i];
			i++;
		}
		z = 0;
		while (env[z])
		{
			if (env[z][0] != '\0')
				i--;
			position = ft_check_env_item(shell, env[z]);
			if (position < 0)
				new_env[i + z] = env[z];
			else
				new_env[i] = env[z];
			z++;
		}
	}
	return (0);
}
