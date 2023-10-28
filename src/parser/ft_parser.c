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
#include "../includes/minishell.h"

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
	free(index->token_str);
	index->token_str = index->next->token_str;
	shell->token_list = index->next->next;
	free(index->next);
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

void	ft_parser(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	int i;

	i = 0;
	shell->command_list = NULL;
	while (shell->token_list)
	{
		tmp_cmd = (t_cmd *) malloc (sizeof(t_cmd));
		tmp_cmd->order_id = i;
		tmp_cmd->arg_nbr = ft_command_args_number(shell->token_list) + 1;
		tmp_cmd->sim_cmd = (char **) malloc (sizeof(char *) \
		* tmp_cmd->arg_nbr);
		tmp_cmd->redir = NULL;
		tmp_cmd->next = NULL;
		ft_create_command(shell, tmp_cmd);
		ft_check_redir(tmp_cmd);
		ft_add_command(shell, tmp_cmd);
		i++;
	}
}

void ft_print_elements_char(t_shell *shell)
{
	t_token	*command = shell->command_list->redir;
	int i = 1;
	int j = 0;

	while (command)
	{
		printf("%d. command: *%d* word: *%s*\n", i, j, command->token_str);
		j++;
		i++;
	}
	command = command->next;
}

void ft_print_elements_redir(t_shell *shell)
{
	t_cmd *listaredir;
	int i = 1;

	listaredir = shell->command_list;

	while (listaredir)
	{
		if (!listaredir->redir)
		{
			printf("nao tinha redir\n");

		}
		else
		{
			printf("%d. token redir: *%s* e name: *%d*\n", i, listaredir->redir->token_str, listaredir->redir->name);
		}
		listaredir = listaredir->next;
	}
}
