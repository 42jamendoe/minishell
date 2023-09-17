/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_char(char *prompt, int i)
{
	if (prompt[i] == '|' || prompt[i] == '>' || prompt[i] == '<')
		return (TOKEN);
	else
		return (WORD);
}

void	ft_add_new(t_shell *shell)
{
	t_token	*tmp;

	tmp = (shell->token_list);
	if (!(shell->token_list))
	{
		(shell->token_list) = shell->token_new;
		(shell->token_list)->id = 1;
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

int	ft_create_token(t_shell *shell, int i)
{
	char	*tmp_token;
	int		j;

	j = 2;
	if ((shell->prompt)[i + 1] == '<' || (shell->prompt)[i + 1] == '>')
	{
		j++;
		tmp_token = (char *) malloc (sizeof(char) * 2 + 1);
		tmp_token[0] = (shell->prompt)[i];
		tmp_token[1] = (shell->prompt)[i + 1];
		tmp_token[2] = '\0';
	}
	else
	{
		tmp_token = (char *) malloc (sizeof(char) * 1 + 1);
		tmp_token[0] = (shell->prompt)[i];
		tmp_token[1] = '\0';
	}
	shell->new_tok = ft_create_item(tmp_token, TOKEN);
	ft_add_new(&(*shell));
	return (j);
}

int	ft_create_word(t_shell *shell, int i)
{
	int		j;
	char	*tmp_word;

	j = 0;
	while (shell->prompt[i] && shell->prompt[i] == ' ')
		i++;
	if (shell->prompt[i + j] && (shell->prompt[i + j] == '\'' || shell->prompt[i + j] == '"'))
		j += ft_handle_quotes(shell->prompt, i, shell->prompt[i]);
	else
	{
		while (shell->prompt[i + j] && shell->prompt[i + j] != ' ')
			j++;
	}
	tmp_word = ft_substr(&(shell->prompt)[i], 0, j);
	if (!tmp_word)
		return (0);
	shell->new_tok = ft_create_item(tmp_word, WORD);
	ft_add_new(&(*shell));
	return (j);
}

void	ft_lexer(t_shell *shell)
{
	int		i;

	i = 0;
	shell->input = NULL;
	while (shell->prompt[i] != '\0')
	{
		while (shel->prompt[i] == ' ')
			i++;
		if (ft_check_char(shell->prompt, i) == TOKEN)
		{
			i += ft_create_token(&(*shell), i);
		}
		else
		{
			i += ft_create_word(&(*shell), i);
		}
	}
	shell->main_list = shell->input;
}
