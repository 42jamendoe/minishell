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

int	ft_clean_memory(t_shell *shell, int fd)
{
	if (fd > NO_FD)
		close(fd);
	ft_clean_prompt(shell);
	ft_putendl_fd("minishell: error allocating memory", STDERR_FILENO);
	return (EXIT_FAILURE);
}

void	ft_clean_token(t_token *token_to_clean)
{
	t_token	*cl_token;
	t_token	*cl_token_anchor;

	cl_token = token_to_clean;
	cl_token_anchor = NULL;
	token_to_clean = NULL;
	if (cl_token)
	{
		while (cl_token->next)
		{
			if (cl_token->token_str)
				free(cl_token->token_str);
			if (cl_token->next)
				cl_token_anchor = cl_token->next;
			free(cl_token);
			cl_token = cl_token_anchor;
		}
	}
}

void	ft_clean_char(char **char_to_clean)
{
	int	i;

	i = 0;
	if (char_to_clean != NULL)
	{
		while (char_to_clean[i])
		{
			if (char_to_clean[i])
				free(char_to_clean[i]);
			i++;
		}
		free(char_to_clean[i]);
		free(char_to_clean);
	}
}

void	ft_clean_command(t_shell *shell)
{
	t_cmd	*cl_command;
	t_cmd	*cl_command_anchor;

	cl_command = shell->command_list;
	if (cl_command)
	{
		while (cl_command)
		{
			cl_command_anchor = cl_command->next;
			ft_clean_token(cl_command->redir);
			ft_clean_char(cl_command->sim_cmd);
			free(cl_command);
			cl_command = cl_command_anchor;
		}
	}
}

void	ft_clean(t_shell *shell, int error)
{
	ft_clean_command(shell);
	ft_clean_char(shell->env);
	ft_clean_token(shell->token_list);
	free(shell->prompt);
	if (error == 1)
		ft_putendl_fd("minishell: error getting prompt", STDOUT_FILENO);
	rl_clear_history();
	exit (EXIT_FAILURE);
}
