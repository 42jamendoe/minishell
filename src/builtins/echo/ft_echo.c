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

int	ft_echo(t_shell *shell, char **arg)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	(void)shell;
	if (arg[1][0] == '-' && arg[1][1] == 'n')
	{
		i += 2;
		n = 1;
		while (arg[1][i] != '\0' || n == 0)
		{
			if (arg[1][i] != 'n')
				n = 0;
			i++;
		}
	}
	i = 1 + n;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
