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

#include "../includes/minishell.h"

void	ft_add_new(t_shell *shell, t_token *new_token)
{
	t_token	*tmp;

	tmp = shell->tkn_list;
	if (!(shell->tkn_list))
		shell->tkn_list = new_token;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
}

t_token	*ft_create_item(char *str, t_tkn_tp item_type)
{
	t_token	*token_new;

	token_new = (t_token *) malloc (sizeof(t_token));
	if (!token_new)
		return (0);
	token_new->token = str;
	token_new->type = item_type;
	token_new->next = NULL;
	return (token_new);
}

int	ft_handle_quotes(char *prompt, int i, int c)
{
	int	j;

	j = 1;
	if (prompt[i + j] == c)
		return (0);
	else
	{
		while (prompt[i + j] != c)
			j++;
		j++;
	}
	return (j);
}
