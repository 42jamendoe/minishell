/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	ft_check_redir(t_cmd *current_command)
{
	t_token	*tmp_token;

	tmp_token = current_command->redir;
	current_command->in = 0;
	current_command->out = 0;
	current_command->prev_has_redirout = 0;
	if (tmp_token)
	{
		while (tmp_token)
		{
			if (tmp_token->name == LESS || tmp_token->name == LESSLESS)
				current_command->in++;
			else if (tmp_token->name == GREAT || tmp_token->name == GREATGREAT)
			{
				current_command->out++;
				if (current_command->next)
					current_command->next->prev_has_redirout = 1;
			}
			tmp_token = tmp_token->next;
		}
	}
}

int	ft_command_args_number(t_token *index)
{
	int	i;

	i = 0;
	while (index)
	{
		if (index->name == PIPE)
			return (i);
		else if (index->name == WORD)
			i++;
		index = index->next;
	}
	return (i);
}

void	ft_clean_pipe_token(t_shell *shell)
{
	t_token	*anchor;

	anchor = shell->token_list->next;
	free(shell->token_list);
	shell->token_list = anchor;
}

int	ft_check_function(char *str)
{
	if (!ft_strncmp(str, "echo", 5))
		return (1);
	else if (!ft_strncmp(str, "cd", 3))
		return (2);
	else if (!ft_strncmp(str, "pwd", 4))
		return (3);
	else if (!ft_strncmp(str, "export", 7))
		return (4);
	else if (!ft_strncmp(str, "unset", 6))
		return (5);
	else if (!ft_strncmp(str, "env", 4))
		return (6);
	else if (!ft_strncmp(str, "exit", 5))
		return (7);
	else
		return (-1);
}

void	ft_init_count_redir(t_cmd *tmp_cmd)
{
	tmp_cmd->in = 0;
	tmp_cmd->out = 0;
	tmp_cmd->redir = NULL;
	tmp_cmd->next = NULL;
}
