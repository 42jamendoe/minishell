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
#include "../includes/minishell.h"

int ft_remove_spaces(char *check, int i)
{
	while (i > 0)
	{
		if (check[i - 1] == ' ')
			i--;
		else
			break;
		check[i] = '\0';
	}
	return (i);
}

int ft_check_double_pipe(t_shell *shell)
{
	int i;
	char *uni;

	i = 0;
	uni = shell->prompt;
	while (uni[i] != '\0')
	{
		if (uni[i] == '|')
		{
			if (uni[i + 1] != '\0')
			{
				while (uni[i + 1] == ' ' && uni[i + 1] != '\0')
					i++;
				if (uni[i + 1] == '|')
					return (EXIT_FAILURE);
			}
			else if (uni[0] == '|')
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int ft_erase_double_quotes(t_shell *shell, int i, int j)
{
	if (j < 0)
		shell->prompt[i] = ' ';
	else if (shell->prompt[j] != '\0')
	{
		while (shell->prompt[j] == ' ' && shell->prompt[j] != '\0')
			j++;
		if (shell->prompt[j] == '"')
		{
			shell->prompt[i] = ' ';
			shell->prompt[j] = ' ';
			j++;
		}
	}
	return (j);
}

void ft_check_double_quotes(t_shell *shell)
{
	int i;
	int j;
	char *uni;

	i = 0;
	uni = shell->prompt;
	while (uni[i] != '\0')
	{
		j = i + 1;
		if (uni[j] == '"')
		{
			i += ft_erase_double_quotes(shell, i, j);
		}
		else
			i = j;
	}
}

int ft_check_quotes_number(t_shell *shell)
{
	int i;
	int sqt;
	int dqt;

	i = 0;
	sqt = 0;
	dqt = 0;
	while (shell->prompt[i] != '\0')
	{
		if (shell->prompt[i] == '\'')
			sqt = ft_change_quotes_state(shell->prompt[i], sqt, dqt);
		else if (shell->prompt[i] == '"')
			dqt = ft_change_quotes_state(shell->prompt[i], sqt, dqt);
		i++;
	}
	if (sqt || dqt)
	{
		ft_print_error(3);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
