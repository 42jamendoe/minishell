/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	ft_add_new(t_shell *shell, t_token *new_token)
{
	t_token	*token_tmp;

	if (!shell->token_list)
		shell->token_list = new_token;
	else
	{
		token_tmp = shell->token_list;
		while (token_tmp->next)
			token_tmp = token_tmp->next;
		token_tmp->next = new_token;
	}
}

t_token	*ft_create_item(char *token_char, t_token_name token_name)
{
	t_token	*new_token;

	new_token = (t_token *) malloc (sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (token_name != PIPE)
		new_token->token_str = token_char;
	else
		new_token->token_str = NULL;
	new_token->name = token_name;
	new_token->next = NULL;
	return (new_token);
}

int	ft_handle_quotes(char *prompt, int i, int c)
{
	int	j;

	j = 1;
	while (prompt[i + j] != c)
		j++;
	j++;
	return (j);
}

int	ft_command_number(t_shell *shell)
{
	t_token	*tmp_token;
	int		i;

	tmp_token = shell->token_list;
	i = 0;
	if (tmp_token == NULL)
		return (i);
	while (tmp_token)
	{
		if (tmp_token->name == PIPE)
			i++;
		tmp_token = tmp_token->next;
	}
	i++;
	return (i);
}

t_token_name	ft_check_char(char *prompt, int i)
{
	t_token_name	token_name;

	if (prompt[i] == '|')
		token_name = PIPE;
	else if (prompt[i] == '>')
	{
		if (prompt[i + 1] == '>')
			token_name = GREATGREAT;
		else
			token_name = GREAT;
	}
	else if (prompt[i] == '<')
	{
		if (prompt[i + 1] == '<')
			token_name = LESSLESS;
		else
			token_name = LESS;
	}
	else
		token_name = WORD;
	return (token_name);
}
