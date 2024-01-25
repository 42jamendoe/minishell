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
#include "../../includes/minishell.h"

int	ft_create_token(t_shell *shell, int i, t_token_name name)
{
	int	j;

	j = 1;
	if (name == 3 || name == 5)
		j++;
	while (shell->prompt[i + j] == '\0' || shell->prompt[i + j] == ' ' || \
	shell->prompt[i + j] == '|')
		j++;
	return (j);
}

int	ft_next_stop(t_shell *shell, int i, int j)
{
	if (shell->prompt[i + j] == '\'' \
	|| shell->prompt[i + j] == '"')
		j += ft_handle_quotes(shell->prompt, i + j, \
		shell->prompt[i + j]);
	else if (shell->prompt[i + j] != '\0')
		j++;
	return (j);
}

int	ft_create_word(t_shell *shell, int i, t_token_name name)
{
	int		j;
	char	*word_tmp;
	t_token	*new_word;

	j = 0;
	word_tmp = NULL;
	if (name != PIPE)
	{
		while (shell->prompt[i + j] != '\0' && shell->prompt[i + j] \
		!= ' ' && shell->prompt[i + j] != '|')
			j = ft_next_stop(shell, i, j);
		word_tmp = ft_substr(shell->prompt, i, j);
		if (!word_tmp)
			return (ft_lexer_err(shell));
	}
	new_word = ft_create_item(word_tmp, name);
	if (!new_word)
		return (ft_lexer_err(shell));
	ft_add_new(shell, new_word);
	return (j);
}

int	ft_lexer(t_shell *shell)
{
	int				i;
	int				check;
	t_token_name	token_tmp;

	i = 0;
	shell->token_list = NULL;
	while (shell->prompt[i] != '\0')
	{
		while (shell->prompt[i] == ' ')
			i++;
		token_tmp = ft_check_char(shell->prompt, i);
		if (token_tmp != WORD)
			i += ft_create_token(shell, i, token_tmp);
		check = ft_create_word(shell, i, token_tmp);
		if (check < 0)
			return (EXIT_FAILURE);
		else
			i += check;
	}
	shell->cmd_nbr = ft_command_number(shell);
	ft_check_token_valid(shell);
	return (EXIT_SUCCESS);
}
