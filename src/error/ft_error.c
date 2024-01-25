/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	ft_check_token_valid(t_shell *shell)
{
	t_token	*check;

	check = shell->token_list;
	if (check->next)
	{
		if (check->name == check->next->name && check->name != WORD)
		{
			ft_print_error(1);
			if (check->next->name == PIPE)
				ft_putstr_fd("'|'\n", STDERR_FILENO);
			if (check->next->name == GREAT)
				ft_putstr_fd("'>'\n", STDERR_FILENO);
			if (check->next->name == GREATGREAT)
				ft_putstr_fd("'>>'\n", STDERR_FILENO);
			if (check->next->name == LESS)
				ft_putstr_fd("'<<'\n", STDERR_FILENO);
			if (check->next->name == LESSLESS)
				ft_putstr_fd("''\n", STDERR_FILENO);
			return (1);
		}
	}
	return (0);
}

void	ft_check_token_end_last(t_shell *shell, int i)
{
	if (i > 2)
	{
		if (shell->prompt[i - 1] == '>' && shell->prompt[i - 2] == '>')
		{
			ft_print_error(0);
			return ;
		}
		if (shell->prompt[i - 1] == '<' && shell->prompt[i - 2] == '<')
		{
			ft_print_error(0);
			return ;
		}
	}
	if (shell->prompt[i - 1] == '|')
		ft_print_error(0);
	if (shell->prompt[i - 1] == '>')
		ft_print_error(0);
	if (shell->prompt[i - 1] == '<')
		ft_print_error(0);
}

int	ft_check_token_end(t_shell *shell)
{
	int		i;
	char	*check;

	i = 0;
	check = shell->prompt;
	while (check[i] != '\0')
		i++;
	ft_remove_spaces(check, i);
	if (i > 0)
	{
		if (check[i - 1] == '|' || check[i - 1] == '>' || check[i - 1] == '<')
		{
			ft_check_token_end_last(shell, i);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	ft_print_error(int msg)
{
	if (msg == 0)
		ft_putstr_fd("minishell: syntax error near unexpected \
token 'newline'\n", STDERR_FILENO);
	if (msg == 1)
		ft_putstr_fd("minishell: syntax error near unexpected \
token ", STDERR_FILENO);
	if (msg == 2)
		ft_putendl_fd("minishell: syntax error near unexpected \
token '|'", STDERR_FILENO);
	if (msg == 3)
		ft_putendl_fd("minishell: unclosed quote", STDERR_FILENO);
	if (msg == 4)
		ft_putendl_fd("minishell: memory error", STDERR_FILENO);
	if (msg == 5)
		ft_putendl_fd("minishell: command not found", STDERR_FILENO);
}

int	ft_check_syntax(t_shell *shell)
{
	if (shell->prompt)
	{
		add_history(shell->prompt);
		if (ft_check_quotes_number(shell) || ft_check_double_pipe(shell))
		{
			free(shell->prompt);
			return (EXIT_FAILURE);
		}
		if (ft_check_prompt(shell->prompt))
		{
			free(shell->prompt);
			return (EXIT_FAILURE);
		}
		if (ft_check_token_end(shell))
		{
			free(shell->prompt);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
