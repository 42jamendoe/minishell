/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

t_state	ft_define_state(char c, int *dq)
{
	if (c == '\'')
	{
		if ((*dq) == 0)
			return (SQUOTE);
		else
			return (DQUOTEOPEN);
	}
	else if (c == '"')
	{
		(*dq) = 1;
		return (DQUOTE);
	}
	else
		return (DEFAULT);
}

char	*ft_state_is_default(t_shell *shell, char *arg, int *position)
{
	int		anchor;
	char	*expanded;

	anchor = (*position);
	while (arg[(*position)] != '\0' && arg[(*position)] != ' ' \
	&& arg[(*position)] != '\"' && arg[(*position)] != '\'')
		(*position)++;
	expanded = ft_process_arg(shell, arg, anchor, (*position));
	if (arg[(*position)] == ' ' || arg[(*position)] == '\"')
		(*position)++;
	return (expanded);
}

char	*ft_state_is_squote(char *arg, int *position)
{
	int		anchor;
	char	*expanded;

	(*position)++;
	anchor = (*position);
	if ((*position) == '\'')
		expanded = ft_strdup("\0");
	else
	{
		while (arg[(*position)] != '\'')
			(*position)++;
		expanded = ft_expand_text(arg, anchor, (*position));
		(*position)++;
	}
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*ft_state_is_dquote(t_shell *shell, char *arg, \
int *position, t_state arg_state)
{
	int		anchor;
	char	*expanded;

	if (arg_state == DQUOTE)
		(*position)++;
	anchor = (*position);
	while (arg[(*position)] != '\"' && arg[(*position)] != '$')
		(*position)++;
	if ((*position) - anchor == 0 && arg_state == DQUOTE)
	{
		expanded = ft_strdup("\0");
		if (arg[(*position)] == '\"')
			(*position)++;
	}
	else
	{
		expanded = ft_process_arg(shell, arg, anchor, (*position));
		if ((arg[(*position)] == ' ' || arg[(*position)] == '\"') \
		&& arg_state == DQUOTEOPEN)
			(*position)++;
	}
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*ft_expand_dollar(t_shell *shell, char *arg, int anchor, int position)
{
	char	*env_name;
	char	*env_value;
	int		i;

	i = 0;
	env_value = NULL;
	env_name = ft_substr(arg, anchor, position - anchor);
	if (!env_name)
		return (NULL);
	while (shell->env[i])
	{
		if (!ft_str_is_env(shell->env[i], env_name))
			i++;
		else
		{
			env_value = ft_get_env_value(shell->env[i]);
			free(env_name);
			return (env_value);
		}
	}
	free(env_name);
	return ("\0");
}
