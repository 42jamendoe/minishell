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

void	ft_change_quote_state_begin(char *str, int *index, int *sq, int *dq)
{
	if (str[(*index)] == '"' && (*dq) == -1 && (*sq) == -1)
	{
		(*dq) = 1;
		(*index)++;
	}
	else if (str[(*index)] == '\'' && (*dq) == -1 && (*sq) == -1)
	{
		(*sq) = 1;
		(*index)++;
	}
}

void	ft_change_quote_state_end(char *str, int *index, int *sq, int *dq)
{
	if (str[(*index)] == '"' && (*dq) == 1)
	{
		(*dq) = -1;
		(*index)++;
	}
	else if (str[(*index)] == '\'' && (*sq) == 1)
	{
		(*sq) = -1;
		(*index)++;
	}
}

char	*ft_test_change_state(t_shell *shell, \
char *to_expand, int *position, int *sq, int *dq)
{
	char	*tmp_word;

	if ((*dq) == -1 && (*sq) == -1)
		tmp_word = ft_expand_dollar_sign_00(shell, to_expand, &(*position));
	else if ((*dq) == 1 && (*sq) == -1)
		tmp_word = ft_expand_dollar_sign_01(shell, to_expand, &(*position));
	else if ((*sq) == 1)
	{
		tmp_word = ft_expand_dollar_sign_1_(shell, to_expand, &(*position));
		(*sq) *= -1;
	}
	else if ((*dq) == 1 && (*sq) == 1)
		tmp_word = ft_expand_dollar_sign_11(shell, to_expand, &(*position));
	ft_change_quote_state_end(to_expand, &(*position), &(*sq), &(*dq));
	return (tmp_word);
}

char	*ft_join_not_null(char *join, char *expanded)
{
	if (join)
		return (join);
	free(expanded);
	return (NULL);
}
