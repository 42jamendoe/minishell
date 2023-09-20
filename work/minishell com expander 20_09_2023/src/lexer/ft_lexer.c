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

t_tkn_tp	ft_check_char(char *prompt, int i)
{
	t_tkn_tp	c_token;

	if (prompt[i] == '|')
		c_token = PIPE;
	else if (prompt[i] == '>')
	{
		if (prompt[i + 1] == '>')
			c_token = GREATGREAT;
		else
			c_token = GREAT;
	}
	else if (prompt[i] == '<')
	{
		if (prompt[i + 1] == '<')
			c_token = LESSLESS;
		else
			c_token = LESS;
	}
	else
		c_token = WORD;
	return (c_token);
}

int	ft_create_token(t_shell *shell, int i, t_tkn_tp tmp_tkn)
{
	char	*tmp_token;
	t_token	*new_token;
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
	new_token = ft_create_item(tmp_token, tmp_tkn);
	ft_add_new(shell, new_token);
	return (j);
}

int	ft_create_word(t_shell *shell, int i)
{
	int		j;
	char	*tmp_word;
	t_token	*new_word;

	j = 0;
	while (shell->prompt[i] && shell->prompt[i] == ' ')
		i++;
	if (shell->prompt[i + j] && (shell->prompt[i + j] == '\'' \
	|| shell->prompt[i + j] == '"'))
		j += ft_handle_quotes(shell->prompt, i, shell->prompt[i]);
	else
	{
		while (shell->prompt[i + j] && shell->prompt[i + j] != ' ')
			j++;
	}
	tmp_word = ft_substr(&shell->prompt[i], 0, j);
	if (!tmp_word)
		return (0);
	new_word = ft_create_item(tmp_word, WORD);
	ft_add_new(shell, new_word);
	return (j);
}

void	ft_lexer(t_shell *shell)
{
	int			i;
	t_tkn_tp	tmp_tkn;

	i = 0;
	shell->tkn_list = NULL;
	while (shell->prompt[i] != '\0')
	{
		while (shell->prompt[i] == ' ')
			i++;
		tmp_tkn = ft_check_char(shell->prompt, i);
		if (tmp_tkn == WORD)
			i += ft_create_word(shell, i);
		else
			i += ft_create_token(shell, i, tmp_tkn);
	}
}

//Falta tratar malloc caso falhe nas linhas 50 e 57