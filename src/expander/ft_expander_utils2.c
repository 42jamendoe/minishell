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

char	*ft_expand_text(char *arg, int anchor, int *position)
{
	char	*tmp_text;
	int		len;

	len = (*position) - anchor;
	tmp_text = ft_substr(arg, anchor, len);
	if (!tmp_text)
		return (NULL);
	return (tmp_text);
}

char	*ft_expand_var(t_shell *shell, char *arg, int anchor, int *position)
{
	char	*expanded;

	if (arg[anchor] == '\?')
		expanded = ft_itoa(g_status);
	else
		expanded = ft_expand_dollar(shell, arg, anchor, &(*position));
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*ft_get_env_value(char *env)
{
	size_t	len;
	int		equal;
	char	*env_value;

	len = ft_strlen(env);
	equal = ft_position_of_equal(env);
	env_value = ft_substr(env, equal + 1, len - equal);
	if (!env_value)
		return (NULL);
	return (env_value);
}

void	ft_change_quote_state_begin(char *str, int *index, int quotes[2])
{
	if (str[(*index)] == '"' && (quotes[1]) == -1 && (quotes[0]) == -1)
	{
		(quotes[1]) = 1;
		(*index)++;
	}
	else if (str[(*index)] == '\'' && (quotes[1]) == -1 && (quotes[0]) == -1)
	{
		(quotes[0]) = 1;
		(*index)++;
	}
}

void	ft_change_quote_state_end(char *str, int *index, int quotes[2])
{
	if (str[(*index)] == '"' && (quotes[1]) == 1)
	{
		(quotes[1]) = -1;
		(*index)++;
	}
	else if (str[(*index)] == '\'' && (quotes[0]) == 1)
	{
		(quotes[0]) = -1;
		(*index)++;
	}
}
