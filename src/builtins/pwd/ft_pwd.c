/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*current_working_diretory;

	current_working_diretory = NULL;
	current_working_diretory = getcwd(current_working_diretory, 0);
	if (!current_working_diretory)
	{
		ft_putendl_fd("Minishell: Can't find cwd\n", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(current_working_diretory, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
