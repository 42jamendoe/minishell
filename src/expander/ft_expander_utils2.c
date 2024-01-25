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

char	*ft_get_substring(t_shell *shell, char *str, int *position)
{
	int		anchor;
	char	*tmp_word;

	anchor = (*position);
	if (str[(*position)] == '$')
	{
		anchor++;
		(*position)++;
		while (str[(*position)] != '$' && str[(*position)] != '\0' \
		&& str[(*position)] != '\'' && str[(*position)] != ' ')
			(*position)++;
		tmp_word = ft_expand_var(shell, str, anchor, &(*position));
	}
	else
	{
		while (str[(*position)] != '$' && str[(*position)] != '\0')
			(*position)++;
		tmp_word = ft_substr(str, anchor, (*position) - anchor);
	}
	return (tmp_word);
}

char	*ft_find_substring(t_shell *shell, char *str, int *position)
{
	char	*exp_word;
	char	*tmp_word;
	char	*join;

	exp_word = ft_strdup("");
	if (!exp_word)
		return (NULL);
	while (str[(*position)] != '\0')
	{
		tmp_word = ft_get_substring(shell, str, position);
		if (!tmp_word)
		{
			join = exp_word;
			return (join);
		}
		else
		{
			join = ft_strjoin(exp_word, tmp_word);
			free(tmp_word);
		}
		free(exp_word);
		exp_word = join;
	}
	return (exp_word);
}
