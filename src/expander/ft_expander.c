/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

char	*ft_exp_command(t_shell *shell, char *tmp_word, char *to_expand, \
int *position)
{
	char	*expanded;
	char	*join;
	int		sq;
	int		dq;

	sq = -1;
	dq = -1;
	join = NULL;
	expanded = tmp_word;
	while (to_expand[(*position)] != '\0')
	{
		ft_change_quote_state_begin(to_expand, &(*position), &sq, &dq);
		if (to_expand[(*position)] == '\0')
			return(ft_join_not_null(join, expanded));
		tmp_word = ft_test_change_state(shell, to_expand, &(*position), &sq, &dq);
		if (!tmp_word)
			join = NULL;
		else
		{
			join = ft_strjoin(expanded, tmp_word);
			free(tmp_word);
		}
		free(expanded);
		expanded = join;
	}
	return (expanded);
}

void	ft_delete_redir_invalid(t_cmd *tmp_cmd, t_token *invalid)
{
	t_token	*anchor;
	t_token	*delete;

	anchor = tmp_cmd->redir;
	if (tmp_cmd->redir->token_str == invalid->token_str)
		tmp_cmd->redir = tmp_cmd->redir->next;
	while (anchor)
	{
		if (anchor->token_str == invalid->token_str)
		{
			free(invalid->token_str);
			delete = anchor;
			anchor = anchor->next;
			free(delete);
			break ;
		}
		else
			anchor = anchor->next;
	}
	ft_check_redir(tmp_cmd);
}

int	ft_exp_redir(t_shell *shell, t_cmd *tmp_cmd)
{
	t_token	*tmp_redir;
	int		position;
	char	*tmp_word;

	tmp_redir = tmp_cmd->redir;
	while (tmp_redir)
	{
		position = 0;
		tmp_word = ft_strdup("");
		if (!tmp_word)
			return (0);
		tmp_word = ft_exp_command(shell, tmp_word, tmp_redir->token_str, &position);
		if (!tmp_word)
			ft_delete_redir_invalid(tmp_cmd, tmp_redir);
		tmp_redir->token_str = tmp_word;
		if (!tmp_redir->next)
			break ;
		tmp_redir = tmp_redir->next;
	}
	return (0);
}

int	ft_expander(t_shell *shell)
{
	t_cmd	*tmp_command;
	char	*tmp_word;
	int		arg_count;
	int		position;

	tmp_command = shell->command_list;
	while (tmp_command)
	{
		arg_count = 1;
		while (tmp_command->sim_cmd[arg_count])
		{
			tmp_word = ft_strdup("");
			if (!tmp_word)
				return (0);
			position = 0;
			tmp_word = ft_exp_command(shell, tmp_word, \
			tmp_command->sim_cmd[arg_count], &position);
			free(tmp_command->sim_cmd[arg_count]);
			tmp_command->sim_cmd[arg_count] = tmp_word;
			arg_count++;
		}
		if (tmp_command->redir)
			ft_exp_redir(shell, tmp_command);
		if (!tmp_command->next)
			break ;
		tmp_command = tmp_command->next;
	}
	return (EXIT_SUCCESS);
}
