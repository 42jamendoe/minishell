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

t_status	ft_define_status(char c)
{
	if (c == '\'')
		return (SQUOTE);
	else if (c == '\"')
		return (DQUOTE);
	else
		return (DEFAULT);
}

char	*ft_expand_dollar(t_shell *shell, char *arg, int *anchor, int *position)
{
	char	*substr;
	char	*env_value;
	t_env	*env_tmp;

	env_value = NULL;
	if (arg[(*position)] == '\0')
		return (NULL);
	while (arg[(*position)] != '\0' && arg[(*position)] != '$')
		(*position)++;
	substr = ft_substr(arg, (*anchor), (*position) - (*anchor));
	env_tmp = shell->env_list;
 	while (env_tmp && env_value == NULL)
	{
		if (ft_strncmp (substr, env_tmp->name, ft_strlen(env_tmp->name)) == 0)
			env_value = env_tmp->value;
		env_tmp = env_tmp->next;
	}
	free(substr);
	if (!env_value)
		return (NULL);
	printf("palavra%s\n", env_value);
	return (env_value);
}
