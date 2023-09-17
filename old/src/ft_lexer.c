/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <editline/readline.h>
#include <stddef.h>

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <editline/readline.h>

int	ft_check_char(char *prompt, int i)
{
	if (prompt[i] == '|' || prompt[i] == '>' || prompt[i] == '<')
		return (TOKEN);
	else
		return (WORD);
}

void	ft_add_new(t_token **token_list, t_token *token_new)
{
	t_token	*tmp;

	tmp = (*token_list);
	if (!(*token_list))
	{
		(*token_list) = token_new;
		(*token_list)->id = 1;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token_new;
		tmp->next->id = tmp->id + 1;
	}
}

t_token	*ft_create_item(char *str, int type)
{
	t_token	*token_new;

	token_new = (t_token *) malloc (sizeof(t_token));
	if (!token_new)
		return (0);
	token_new->token = str;
	token_new->type = type;
	token_new->next = NULL;
	return (token_new);
}

int	ft_handle_quotes(char *prompt, int i, int c)
{
	int	j;

	j = 1;
	if (prompt[i] == c)
		return (0);
	else
	{
		while (prompt[i + j] != c)
			j++;
		j++;
	}
	return (j);
}

int	ft_create_token(t_token **input, char *prompt, int i)
{
	char	*tmp_token;
	t_token	*new_tok;
	int		j;

	j = 2;
	if (prompt[i + 1] == '<' || prompt[i + 1] == '>')
	{
		j++;
		tmp_token = (char *) malloc (sizeof(char) * 2 + 1);
		tmp_token[0] = prompt[i];
		tmp_token[1] = prompt[i + 1];
		tmp_token[2] = '\0';
	}
	else
	{
		tmp_token = (char *) malloc (sizeof(char) * 1 + 1);
		tmp_token[0] = prompt[i];
		tmp_token[1] = '\0';
	}
	new_tok = ft_create_item(tmp_token, TOKEN);
	ft_add_new(&(*input), new_tok);
	return (j);
}

int	ft_create_word(t_token **input, char *prompt, int i)
{
	int		j;
	char	*tmp_word;
	t_token	*new_tok;

	j = 0;
	while (prompt[i] && prompt[i] == ' ')
		i++;
	if (prompt[i + j] && (prompt[i + j] == '\'' || prompt[i + j] == '"'))
		j += ft_handle_quotes(prompt, i, prompt[i]);
	else
	{
		while (prompt[i + j] && prompt[i + j] != ' ')
			j++;
	}
	tmp_word = ft_substr(&prompt[i], 0, j);
	if (!tmp_word)
		return (0);
	new_tok = ft_create_item(tmp_word, WORD);
	ft_add_new(&(*input), new_tok);
	return (j);
}

t_token	*ft_lexer(char *prompt)
{
	int		i;
	t_token	*input;

	i = 0;
	input = NULL;
	while (prompt[i] != '\0')
	{
		while (prompt[i] == ' ')
			i++;
		if (ft_check_char(prompt, i) == TOKEN)
		{
			i += ft_create_token(&input, prompt, i);
		}
		else
		{
			i += ft_create_word(&input, prompt, i);
		}
	}
	return (input);
}
