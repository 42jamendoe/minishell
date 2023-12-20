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

char	*ft_expand_dollar_sign_00(t_shell *shell, char *str, int *index)
{
	int		anchor;
	char	*tmp_word;

	if (str[(*index)] == '$')
	{
		(*index) = ft_ignore_equal(str, (*index), "$");
		anchor = (*index);
		if (str[anchor] == '\0')
			return (ft_strdup("$"));
		if (ft_some_char_in_str(str, (*index), "\"\'", 0))
			anchor = (*index) - 1;
		(*index) = ft_some_char_in_str(str, (*index), " \?$\"\'", 1);
		if (ft_some_char_in_str(str, (*index), "?", 0))
			(*index)++;
		tmp_word = ft_expand_var(shell, str, anchor, &(*index));
	}
	else
	{
		anchor = (*index);
		(*index) = ft_some_char_in_str(str, (*index), "$\"\'", 1);
		tmp_word = ft_expand_text(str, anchor, &(*index));
	}
	return (tmp_word);
}

char	*ft_expand_dollar_sign_01(t_shell *shell, char *str, int *index)
{
	int		anchor;
	char	*tmp_word;

	if (str[(*index)] == '$')
	{
		(*index) = ft_ignore_equal(str, (*index), "$");
		anchor = (*index);
		if (str[anchor] == '\0')
			return (ft_strdup("$"));
		if (ft_some_char_in_str(str, (*index), "\"\' ", 0))
			anchor = (*index) - 1;
		(*index) = ft_some_char_in_str(str, (*index), " \?$\"\'", 1);
		if (ft_some_char_in_str(str, (*index), "\?\'", 0))
			(*index)++;
		tmp_word = ft_expand_var(shell, str, anchor, &(*index));
	}
	else
	{
		anchor = (*index);
		(*index) = ft_some_char_in_str(str, (*index), "$\"\'", 1);
		if (ft_some_char_in_str(str, (*index), "\'", 0))
			(*index)++;
		tmp_word = ft_expand_text(str, anchor, &(*index));
	}
	return (tmp_word);
}

char	*ft_expand_dollar_sign_1_(t_shell *shell, char *str, int *index)
{
	int		anchor;
	char	*tmp_word;

	(void) shell;
	anchor = (*index);
	(*index) = ft_some_char_in_str(str, (*index), "'", 1);
	tmp_word = ft_expand_text(str, anchor, &(*index));
	return (tmp_word);
}

char	*ft_expand_dollar_sign_11(t_shell *shell, char *str, int *index)
{
	int		anchor;
	char	*tmp_word;

	if (str[(*index)] == '$')
	{
		(*index) = ft_ignore_equal(str, (*index), "$");
		anchor = (*index);
		if (str[anchor] == '\0')
			return (ft_strdup("$"));
		if (ft_some_char_in_str(str, (*index), "\"\'", 0))
			anchor = (*index) - 1;
		(*index) = ft_some_char_in_str(str, (*index), " \?$\"\'", 1);
		(*index) += ft_some_char_in_str(str, (*index), "?", 0);
		tmp_word = ft_expand_var(shell, str, anchor, &(*index));
	}
	else
	{
		anchor = (*index);
		(*index) += ft_some_char_in_str(str, (*index), "$\"\'", 1);
		tmp_word = ft_expand_text(str, anchor, &(*index));
	}
	return (tmp_word);
}

char	*ft_test_change_state(t_shell *shell, \
char *to_expand, int *position, int quotes[2])
{
	char	*tmp_word = NULL;

	if ((quotes[1]) == -1 && (quotes[0]) == -1)
		tmp_word = ft_expand_dollar_sign_00(shell, to_expand, &(*position));
	else if ((quotes[1]) == 1 && (quotes[0]) == -1)
		tmp_word = ft_expand_dollar_sign_01(shell, to_expand, &(*position));
	else if ((quotes[0]) == 1)
	{
		tmp_word = ft_expand_dollar_sign_1_(shell, to_expand, &(*position));
		(quotes[0]) *= -1;
	}
	else if ((quotes[1]) == 1 && (quotes[0]) == 1)
		tmp_word = ft_expand_dollar_sign_11(shell, to_expand, &(*position));
	ft_change_quote_state_end(to_expand, &(*position), quotes);
	return (tmp_word);
}
