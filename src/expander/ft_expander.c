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
#include "../includes/minishell.h"

char	*ft_exp_command(t_shell *shell, char *to_expand, int *position)
{
	char	*expanded;
	char	*tmp_word;
	char	*join;
	int		anchor;
	int		sq;
	int		dq;

	sq = -1;
	dq = -1;
	join = NULL;
	expanded = ft_strdup("\0");
	if (!expanded)
		return (NULL);
	while (to_expand[(*position)] != '\0')
	{
		if (to_expand[(*position)] == '"' && dq == -1 && sq == -1)
		{
			dq = 1;
			(*position)++;
		}
		else if (to_expand[(*position)] == '\'' && dq == -1 && sq == -1)
		{
			sq = 1;
			(*position)++;
		}
		if (to_expand[(*position)] == '\0')
		{
			if (join)
				return (join);
			free(expanded);
			return (NULL);
		}
		if (dq == -1 && sq == -1)
		{
			if (to_expand[(*position)] == '$')
			{
				while (to_expand[(*position)] == '$')
					(*position)++;
				if (to_expand[(*position)] == '\0' || to_expand[(*position)] \
				== '"' || to_expand[(*position)] == '\'')
					anchor = (*position) - 1;
				else
					anchor = (*position);
				while (to_expand[(*position)] != '\0' && \
				to_expand[(*position)] != ' ' && to_expand[(*position)] != \
				'\?' && to_expand[(*position)] != '$' && \
				to_expand[(*position)] != '"' && to_expand[(*position)] != '\'')
					(*position)++;
				if (to_expand[(*position)] == '\?')
					(*position)++;
				tmp_word = ft_expand_var(shell, to_expand, anchor, \
				&(*position));
			}
			else 
			{
				anchor = (*position);
				while (to_expand[(*position)] != '\0' && \
				to_expand[(*position)] != \
				'$' && to_expand[(*position)] != '"' && \
				to_expand[(*position)] != '\'')
					(*position)++;
				tmp_word = ft_expand_text(to_expand, anchor, &(*position));
			}
		}
		else if (dq == 1 && sq == -1)
		{
			if (to_expand[(*position)] == '$')
			{
				while (to_expand[(*position)] == '$')
					(*position)++;
				if (to_expand[(*position)] == '\0' || to_expand[(*position)] \
				== '"' || to_expand[(*position)] == '\'' || \
				to_expand[(*position)] == ' ')
					anchor = (*position) - 1;
				else
					anchor = (*position);
				while (to_expand[(*position)] != '\0' && \
				to_expand[(*position)] != ' ' && to_expand[(*position)] \
				!= '\?' && to_expand[(*position)] != '$' && \
				to_expand[(*position)] != '"' && to_expand[(*position)] != '\'')
					(*position)++;
				if (to_expand[(*position)] == '\?' || \
				to_expand[(*position)] == '\'')
					(*position)++;
				tmp_word = ft_expand_var(shell, to_expand, \
				anchor, &(*position));
			}
			else 
			{
				anchor = (*position);
				while (to_expand[(*position)] != '\0' && \
				to_expand[(*position)] != '$' && to_expand[(*position)] != '"' \
				&& to_expand[(*position)] != '\'')
					(*position)++;
				if (to_expand[(*position)] == '\'')
					(*position)++;
				tmp_word = ft_expand_text(to_expand, anchor, &(*position));
			}
		}
		else if (sq == 1)
		{
			anchor = (*position);
			while (to_expand[(*position)] != '\0' \
			&& to_expand[(*position)] != '\'')
				(*position)++;
			tmp_word = ft_expand_text(to_expand, anchor, &(*position));
			sq *= -1;
		}
		else if (dq == 1 && sq == 1)
		{
			if (to_expand[(*position)] == '$')
			{
				while (to_expand[(*position)] == '$')
					(*position)++;
				if (to_expand[(*position)] == '\0' || to_expand[(*position)] \
				== '"' || to_expand[(*position)] == '\'')
					anchor = (*position) - 1;
				else
					anchor = (*position);
				while (to_expand[(*position)] != '\0' && to_expand[(*position)] \
				!= ' ' && to_expand[(*position)] != '\?' && \
				to_expand[(*position)] != '$' && to_expand[(*position)] \
				!= '"' && to_expand[(*position)] != '\'')
					(*position)++;
				if (to_expand[(*position)] == '\?')
					(*position)++;
				tmp_word = ft_expand_var(shell, to_expand, anchor, \
				&(*position));
			}
			else 
			{
				anchor = (*position);
				while (to_expand[(*position)] != '\0' && to_expand[(*position)] \
				!= '$' && to_expand[(*position)] != '"' \
				&& to_expand[(*position)] != '\'')
					(*position)++;
				tmp_word = ft_expand_text(to_expand, anchor, &(*position));
			}
		}
		if (to_expand[(*position)] == '"' && dq == 1)
		{
			dq = -1;
			(*position)++;
		}
		else if (to_expand[(*position)] == '\'' && sq == 1)
		{
			sq = -1;
			(*position)++;
		}
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
		tmp_word = ft_exp_command(shell, tmp_redir->token_str, &position);
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
			position = 0;
			tmp_word = ft_exp_command(shell, \
			tmp_command->sim_cmd[arg_count], &position);
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
