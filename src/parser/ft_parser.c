/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	ft_build_redirection_list(t_shell *shell, t_cmd *command)
{
	t_token	*index;
	t_token	*anchor;

	if (!command->redir)
		command->redir = shell->token_list;
	else
	{
		anchor = command->redir;
		while (anchor->next)
			anchor = anchor->next;
		anchor->next = shell->token_list;
	}
	index = shell->token_list;
	shell->token_list = index->next;
	index->next = NULL;
}

void	ft_build_simple_command(t_shell *shell, int i, t_cmd *command)
{
	t_token	*index;
	t_token	*tmp_command;

	index = shell->token_list;
	command->sim_cmd[i] = index->token_str;
	if (index->next)
		tmp_command = index->next;
	else
		tmp_command = NULL;
	free(shell->token_list);
	shell->token_list = tmp_command;
}

void	ft_create_command(t_shell *shell, t_cmd *command)
{
	int		i;
	int		end;

	i = 0;
	end = 0;
	while (shell->token_list && end == 0)
	{
		if (shell->token_list->name == WORD)
		{
			ft_build_simple_command(shell, i, command);
			i++;
		}
		else if (shell->token_list->name >= LESS && \
		shell->token_list->name <= GREATGREAT)
			ft_build_redirection_list(shell, &(*command));
		else if (shell->token_list->name == PIPE)
		{
			ft_clean_pipe_token(shell);
			end = 1;
		}
	}
	command->sim_cmd[i] = NULL;
}

void	ft_add_command(t_shell *shell, t_cmd *command)
{
	t_cmd	*anchor;

	if (!shell->command_list)
		shell->command_list = command;
	else
	{
		anchor = shell->command_list;
		while (anchor->next)
			anchor = anchor->next;
		anchor->next = command;
	}
}

int	ft_parser(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	int		i;

	i = 0;
	shell->command_list = NULL;
	while (shell->token_list)
	{
		tmp_cmd = (t_cmd *) malloc (sizeof(t_cmd));
		if (!tmp_cmd)
			return (ft_clean_memory(shell, NO_FD));
		tmp_cmd->order_id = i;
		tmp_cmd->pid_cmd = 0;
		tmp_cmd->arg_nbr = ft_command_args_number(shell->token_list) + 1;
		tmp_cmd->sim_cmd = (char **) malloc (sizeof(char *) \
		* tmp_cmd->arg_nbr);
		if (!tmp_cmd->sim_cmd)
			return (ft_clean_memory(shell, NO_FD));
		ft_init_count_redir(tmp_cmd);
		ft_create_command(shell, tmp_cmd);
		ft_check_redir(tmp_cmd);
		tmp_cmd->function_name = ft_check_function(tmp_cmd->sim_cmd[0]);
		ft_add_command(shell, tmp_cmd);
		i++;
	}
	return (EXIT_SUCCESS);
}
