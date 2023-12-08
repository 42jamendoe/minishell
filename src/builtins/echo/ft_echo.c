/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"

int	ft_valid_option(t_cmd *tmp_cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (tmp_cmd->sim_cmd[1][1] == 'n')
	{
		i += 2;
		n = 1;
		while (tmp_cmd->sim_cmd[1][i] != '\0' && n == 1)
		{
			if (tmp_cmd->sim_cmd[1][i] != 'n')
				n = 0;
			i++;
		}
	}
	return (n);
}

int	ft_echo(t_cmd *tmp_cmd)
{
	int		i;
	int		n;

	n = 0;
	if (tmp_cmd->sim_cmd[1])
	{
		if (tmp_cmd->sim_cmd[1][0] == '-')
			n = ft_valid_option(tmp_cmd);
	}
	i = 1 + n;
	while (tmp_cmd->sim_cmd[i])
	{
		ft_putstr_fd(tmp_cmd->sim_cmd[i], STDOUT_FILENO);
		if (tmp_cmd->sim_cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
