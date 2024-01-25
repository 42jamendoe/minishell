/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	ft_clean_prompt(t_shell *shell)
{
	ft_clean_command(shell);
	ft_clean_token(shell->token_list);
	free(shell->prompt);
	return (EXIT_FAILURE);
}

void	ft_clean_exit(t_shell *shell)
{
	if (shell->command_list)
		ft_clean_command(shell);
	if (shell->env)
		ft_clean_char(shell->env);
	if (shell->token_list)
		ft_clean_token(shell->token_list);
}

void	ft_clean_env_invalid(char **list, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(list[j]);
		j++;
	}
	free(list);
	ft_putendl_fd("minishell: couldn't create env<./minishell>", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}
