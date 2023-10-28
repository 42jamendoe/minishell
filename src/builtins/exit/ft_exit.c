/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"
long long status;

void	ft_exit(t_shell *shell, char **arg)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	(void)shell;
	ft_putendl_fd("exit", STDOUT_FILENO);
	while (arg[i])
		i++;
	if (i == 2)
	{
		while (arg[1][j])
		{
			if (!ft_isdigit(arg[1][j]))
			{
				if (arg[1][0] != '-' || arg[1][0] != '+')
				{
					ft_putstr_fd("exit:", STDOUT_FILENO);
					ft_putstr_fd(arg[1], STDOUT_FILENO);
					ft_putendl_fd(": numeric argument required", STDOUT_FILENO);
					status = 2;
				}
			}				
			j++;
		}
		status = ft_atoll(arg[1]);
	}
	else if (i > 2)
	{
		status = EXIT_FAILURE;
		ft_putendl_fd(" exit: too many arguments\n", STDERR_FILENO);
	}
	else
		status = EXIT_SUCCESS;
	exit(status);
}
