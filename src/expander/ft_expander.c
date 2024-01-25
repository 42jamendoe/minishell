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

	expanded = tmp_word;
	while (to_expand[(*position)] != '\0')
	{
		tmp_word = ft_search_stop(shell, to_expand, &(*position));
		if (!tmp_word)
			return (NULL);
		else
		{
			join = ft_strjoin(expanded, tmp_word);
			free(tmp_word);
			free(expanded);
		}
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
		tmp_word = ft_exp_command(shell, tmp_word, \
		tmp_redir->token_str, &position);
		if (!tmp_word)
			ft_delete_redir_invalid(tmp_cmd, tmp_redir);
		tmp_redir->token_str = tmp_word;
		if (!tmp_redir->next)
			break ;
		tmp_redir = tmp_redir->next;
	}
	return (0);
}

int	ft_loop_tmp_word(t_shell *shell, t_cmd *cmd)
{
	int		arg_count;
	int		position;
	char	*tmp_word;
	t_cmd	*tmp_cmd;

	arg_count = 0;
	tmp_cmd = cmd;
	while (tmp_cmd->sim_cmd[arg_count])
	{
		tmp_word = ft_strdup("");
		if (!tmp_word)
			return (EXIT_FAILURE);
		position = 0;
		tmp_word = ft_exp_command(shell, tmp_word, \
		tmp_cmd->sim_cmd[arg_count], &position);
		if (!tmp_word)
			return (EXIT_FAILURE);
		free(tmp_cmd->sim_cmd[arg_count]);
		tmp_cmd->sim_cmd[arg_count] = tmp_word;
		arg_count++;
		if (!tmp_cmd->sim_cmd[arg_count])
			break ;
	}
	return (EXIT_SUCCESS);
}

int	ft_expander(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->command_list;
	while (cmd)
	{
		if (cmd->sim_cmd[0])
		{
			if (ft_loop_tmp_word(shell, cmd))
				return (EXIT_FAILURE);
		}
		if (cmd->redir)
			ft_exp_redir(shell, cmd);
		if (!cmd->next)
			break ;
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
