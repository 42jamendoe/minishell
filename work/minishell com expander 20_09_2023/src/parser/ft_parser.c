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

void	ft_build_rediretion_list(t_shell *shell, t_cmd *tmp_cmd)
{
	t_token	*index;
	t_token	*anchor;

	index = shell->tkn_list;
	if (!tmp_cmd->redir)
		tmp_cmd->redir = index;
	else
	{
		anchor = tmp_cmd->redir;
		while (anchor->next)
			anchor = anchor->next;
		anchor->next = index;
	}
	anchor = index;
	free(shell->tkn_list->token);
	shell->tkn_list->token = shell->tkn_list->next->token;
	if (index->next->next)
		index = index->next->next;
	else
		index = NULL;
	free(shell->tkn_list->next);
	shell->tkn_list = index;
	anchor->next = NULL;
}

void	ft_build_simple_command(t_shell *shell, int i, t_cmd *tmp_cmd)
{
	t_token	*index;
	t_token	*tmp_move_cmd;

	index = shell->tkn_list;
	tmp_cmd->sim_cmd[i] = index->token;
	tmp_move_cmd = shell->tkn_list->next;
	if (index->next)
		tmp_move_cmd = index->next;
	else
		tmp_move_cmd = NULL;
	free(shell->tkn_list);
	shell->tkn_list = tmp_move_cmd;
}

void	ft_create_cmd(t_shell *shell, t_cmd *tmp_cmd)
{
	int		i;

	i = 0;
	while (shell->tkn_list)
	{
		if (shell->tkn_list->type == 0)
		{
			ft_build_simple_command(shell, i, &(*tmp_cmd));
			i++;
		}
		else if (shell->tkn_list->type > 1)
			ft_build_rediretion_list(shell, &(*tmp_cmd));
		else if (shell->tkn_list->type == 1)
		{
			ft_pipe_clean(shell);
			break ;
		}
	}
}

void	ft_add_cmd(t_shell *shell, t_cmd *tmp_cmd)
{
	t_cmd	*move_cmd;

	if (!shell->cmd_list)
		shell->cmd_list = tmp_cmd;
	else
	{
		move_cmd = shell->cmd_list;
		while (move_cmd->next)
			move_cmd = move_cmd->next;
		move_cmd->next = tmp_cmd;
	}
}

void	ft_parser(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	t_token	*index;	

	shell->cmd_list = NULL;
	while (shell->tkn_list)
	{
		tmp_cmd = (t_cmd *) malloc (sizeof(t_cmd));
		index = shell->tkn_list;
		tmp_cmd->arg_nbr = ft_cmd_arg_nbr(index);
		tmp_cmd->sim_cmd = (char **) malloc (sizeof(char *) \
		* tmp_cmd->arg_nbr);
		tmp_cmd->redir = NULL;
		tmp_cmd->next = NULL;
		ft_create_cmd(shell, &(*tmp_cmd));
		ft_add_cmd(shell, &(*tmp_cmd));
	}
}
