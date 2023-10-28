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

#include "../includes/minishell.h"

t_state	ft_define_state(char c)
{
	if (c == '\'')
		return (SQUOTE);
	else if (c == '"')
		return (DQUOTE);
	else
		return (DEFAULT);
}

char	*ft_expand_dollar(char *arg, int anchor, int position)
{
	char	*env_name;
	char	*env_value;

	env_value = NULL;
	env_name = ft_substr(arg, anchor, position - anchor);
	if (!env_name)
		ft_clean();
	env_value = getenv(env_name);
	free(env_name);
	if (!env_value)
		ft_clean();
	return (env_value);
}
