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
#include "../includes/minishell.h"

int	ft_check_token_valid(t_shell *shell)
{
	t_token *check;

	check = shell->token_list;
	if (check->next)
	{
		if(check->name == check->next->name && check->name != WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", STDERR_FILENO);
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
		check = check->next;
	}
	return (0);
}

void	ft_check_token_end_last(t_shell *shell, int i)
{	
		if (i > 2)
		{
			if (shell->prompt[i - 1] == '>' && shell->prompt[i - 2] == '>')
			{
				ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", STDERR_FILENO);
				return ;
			}
			if (shell->prompt[i - 1] == '<' && shell->prompt[i - 2] == '<')
			{
				ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", STDERR_FILENO);
				return ;
			}
		}
		if(shell->prompt[i - 1] == '|')
			ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", STDERR_FILENO);
		if(shell->prompt[i - 1] == '>')
			ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", STDERR_FILENO);
		if(shell->prompt[i - 1] == '<')
			ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", STDERR_FILENO);
}


int	ft_check_token_end(t_shell *shell)
{
	int		i;
	char	*check;

	i = 0;
	check = shell->prompt;
	if (ft_check_double_pipe(shell))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token '|'", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (check[i] != '\0')
		i++;
	while (i > 0)
	{
		if (check[i - 1] == ' ')
			i--;
		else
			break ;
		check[i] = '\0';
	}
	if (i > 0)
	{
		if (check[i - 1] == '|' || check[i - 1] == '>' || check[i - 1] == '<')
		{
			ft_check_token_end_last(shell, i);
			add_history(shell->prompt);
			free(shell->prompt);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_check_double_pipe(t_shell *shell)
{
	int		i;
	char	*uni;

	i = 0;
	uni = shell->prompt;
	while (uni[i] != '\0')
	{
		if (uni[i] == '|')
		{
			if (uni[i + 1] != '\0')
			{
				if (uni[i + 1] == '|')
					return (EXIT_FAILURE);
				while (uni[i + 1] == ' ' && uni[i + 1] != '\0')
					i++;
				if (uni[i + 1] == '|')
					return (EXIT_FAILURE);
			}
			else if (uni[0] == '|')
				return (EXIT_FAILURE);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}


void ft_erase_double_quotes(t_shell *shell, int i, int j)
{
	if (j < 0)
		shell->prompt[i] = ' ';
	else
	{
		shell->prompt[i] = ' ';
		shell->prompt[j] = ' ';
	}

}

void	ft_check_double_quotes(t_shell *shell)
{
	int		i;
	int j;
	char	*uni;

	i = 0;
	uni = shell->prompt;
	while (uni[i] != '\0')
	{
		j = i + 1;
		if (uni[i] == '"')
		{
			if (uni[j] != '\0')
			{
				if (uni[j] == '"')
					ft_erase_double_quotes(shell, i, j);
				while (uni[j] == ' ' && uni[j] != '\0')
					j++;
				if (uni[j] == '|')
					ft_erase_double_quotes(shell, i, j);
			}
			else if (uni[0] == '"')
				ft_erase_double_quotes(shell, i, -1);
		}
		else
			i = j;
	}
}
