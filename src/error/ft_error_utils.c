/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	ft_remove_spaces(char *check, int i)
{
	while (i > 0)
	{
		if (check[i - 1] == ' ')
			i--;
		else
			break ;
		check[i] = '\0';
	}
	return (i);
}

int	ft_check_double_pipe(t_shell *shell)
{
	int	i;
	int	quotes[2];

	i = -1;
	quotes[0] = -1;
	quotes[1] = -1;
	while (shell->prompt[++i] != '\0')
	{
		if (shell->prompt[i] == '|' && (quotes[0] == -1 && quotes[1] == -1))
		{
			while (shell->prompt[i] == '|' || shell->prompt[i] == ' ')
			{
				i++;
				if (shell->prompt[i] == '|')
					return (EXIT_FAILURE);
			}
		}
		if (shell->prompt[i] == '\'' && quotes[1] == -1)
			quotes[0] *= -1;
		else if (shell->prompt[i] == '"' && quotes[0] == -1)
			quotes[1] *= -1;
	}
	if (shell->prompt[i] == '\0' && (quotes[0] == 1 || quotes[1] == 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_check_quotes_number(t_shell *shell)
{
	int	i;
	int	sqt;
	int	dqt;

	i = 0;
	sqt = -1;
	dqt = -1;
	while (shell->prompt[i] != '\0')
	{
		if (shell->prompt[i] == '\'' && dqt == -1)
			sqt *= -1;
		else if (shell->prompt[i] == '"' && sqt == -1)
			dqt *= -1;
		i++;
	}
	if (shell->prompt[i] == '\0' && (sqt == 1 || dqt == 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
