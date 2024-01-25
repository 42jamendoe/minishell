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
#include "../../includes/minishell.h"

char	*ft_expand_double_quotes(t_shell *shell, char *str)
{
	char	*tmp_word;
	char	*expanded;
	char	*join;
	int		index;

	index = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	while (str[(index)] != '\0')
	{
		tmp_word = ft_find_substring(shell, str, &index);
		if (!tmp_word)
			join = tmp_word;
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

char	*ft_stop_dollar(t_shell *shell, char *str, int *position)
{
	int		anchor;
	char	*end;

	(*position)++;
	anchor = (*position);
	while ((str[(*position)] != '\'' && str[(*position)] != '\"' \
	&& str[(*position)] != '\?' && str[(*position)] != '\0'))
		(*position)++;
	end = ft_expand_var (shell, str, anchor, &(*position));
	if (!end)
		return (NULL);
	if (str[(*position)] != '\0')
		(*position)++;
	return (end);
}

char	*ft_stop_single_quote(char *str, int *position)
{
	int		anchor;
	char	*end;

	(*position)++;
	anchor = (*position);
	while (str[(*position)] != '\'')
		(*position)++;
	end = ft_substr(str, anchor, (*position) - anchor);
	if (!end)
		return (NULL);
	(*position)++;
	return (end);
}

char	*ft_stop_double_quotes(t_shell *shell, char *str, int *position)
{
	int		anchor;
	char	*tmp_text;
	char	*end;

	(*position)++;
	anchor = (*position);
	while (str[(*position)] != '\"')
		(*position)++;
	tmp_text = ft_substr(str, anchor, (*position) - anchor);
	if (!tmp_text)
		return (NULL);
	end = ft_expand_double_quotes(shell, tmp_text);
	free(tmp_text);
	if (!end)
		return (NULL);
	(*position)++;
	return (end);
}

char	*ft_search_stop(t_shell *shell, char *str, int *position)
{
	int		anchor;
	char	*end;

	anchor = (*position);
	if (str[(*position)] == '\0')
		return (NULL);
	end = NULL;
	if (str[(*position)] == '\"')
		end = ft_stop_double_quotes(shell, str, &(*position));
	else if (str[(*position)] == '\'')
		end = ft_stop_single_quote(str, &(*position));
	else if (str[(*position)] == '$')
		end = ft_stop_dollar(shell, str, &(*position));
	else
	{
		while ((str[(*position)] != '\'' && str[(*position)] != '\"' \
		&& str[(*position)] != '\0'))
			(*position)++;
		end = ft_substr(str, anchor, (*position) - anchor);
		if (!end)
			return (NULL);
	}
	return (end);
}
