/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	ft_change_quotes_state(int c, int sqt, int dqt)
{
	if (c == '\'')
	{
		if (!dqt && !sqt)
			sqt = 1;
		else if (!dqt && sqt)
			sqt = 0;
		else
			sqt = 0;
		return (sqt);
	}
	if (c == '"')
	{
		if (!dqt && !sqt)
			dqt = 1;
		else if (!dqt && sqt)
			dqt = 0;
		else
			dqt = 0;
		return (dqt);
	}
	ft_print_error(3);
	return (-1);
}

int	ft_error_getting_line(t_shell *shell)
{
	if (shell->prompt)
		free(shell->prompt);
	ft_print_error(4);
	return (-1);
}

int	ft_lexer_err(t_shell *shell)
{
	ft_clean_prompt(shell);
	ft_putendl_fd("error getting command", STDERR_FILENO);
	return (-1);
}
