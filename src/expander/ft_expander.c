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

char	*ft_expand_arg(t_shell *shell, char *arg, int *position, int *dq)
{
	t_state		arg_state;
	char		*expanded;

	expanded = NULL;
	arg_state = ft_define_state(arg[(*position)], &(*dq));
	if (arg_state == DEFAULT  || arg_state == DQUOTEOPEN)
	{
		expanded = ft_state_is_default(shell, arg, &(*position));
	}
	else if (arg_state == SQUOTE)
	{
		expanded = ft_state_is_squote(arg, &(*position));
	}
	else if (arg_state == DQUOTE)
	{
		expanded = ft_state_is_dquote(shell, arg, &(*position), &(*dq));
	}
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*ft_exp_command(t_shell *shell, t_cmd *tmp_cmd, int nbr, int position)
{
	char	*expanded;
	char	*tmp_word;
	char	*join;
	int		dq;

	dq = 0;
	join = NULL;
	expanded = ft_strdup("\0");
	if (!expanded)
		return (NULL);
	while (tmp_cmd->sim_cmd[nbr][position] != '\0')
	{
		tmp_word = ft_expand_arg(shell, tmp_cmd->sim_cmd[nbr], &position, &dq);
		if (!tmp_word)
			join = ft_strdup(expanded);
		else if (expanded[0] == '\0')
			join = tmp_word;
		else
		{
			join = ft_strjoin(expanded, tmp_word);
			free(tmp_word);
		}
		if (!join)
			return (NULL);
		free(expanded);
		expanded = join;
		if (dq == 1)
			position++;
	}
	return (expanded);
}

char	*ft_join_string(t_shell *shell, t_token *tmp_redir, \
char *expanded, int *dq)
{
	char	*tmp_word;
	char	*join;
	int		position;

	position = 0;
	while (tmp_redir->token_str[position] != '\0')
	{
		tmp_word = ft_expand_arg(shell, tmp_redir->token_str, \
		&position, &(*dq));
		join = ft_strjoin(expanded, tmp_word);
		if (!join)
			return (NULL);
		free(expanded);
		free(tmp_word);
		expanded = join;
	}
	return (expanded);
}

int	ft_exp_redir(t_shell *shell, t_cmd *tmp_cmd)
{
	t_token	*tmp_redir;
	char	*expanded;
	int		dq;

	tmp_redir = tmp_cmd->redir;
	while (tmp_redir)
	{
		dq = 0;
		expanded = ft_strdup("\0");
		if (!expanded)
			return (-1);
		expanded = ft_join_string(shell, tmp_redir, expanded, &dq);
		free(tmp_redir->token_str);
		tmp_redir->token_str = expanded;
		tmp_redir = tmp_redir->next;
	}
	return (0);
}

void	ft_expander(t_shell *shell)
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
			tmp_word = ft_exp_command(shell, tmp_command, arg_count, position);
			tmp_command->sim_cmd[arg_count] = tmp_word;
			arg_count++;
		}
		if (tmp_command->redir)
			ft_exp_redir(shell, tmp_command);
		if (!tmp_command->next)
			break ;
		tmp_command = tmp_command->next;
	}
}
