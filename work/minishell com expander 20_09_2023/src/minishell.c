/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:22:03 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_env	*env_tmp;
	t_env	*env_tmp1;
	char	*str_tmp;
	int		i;

	shell.env_list = NULL;
	i = 0;
	if (argc > 1 && *argv[1])
		return (0);
	while (envp[i])
	{
		env_tmp = ft_new_env_item(envp[i]);
		ft_add_new_item(&shell, &(*env_tmp));
		i++;
	}
	env_tmp1 = shell.env_list;
	while (env_tmp1->next)
	{
		env_tmp1 = env_tmp1->next;
	}
	while (1)
	{
		str_tmp = readline("minishell$");
		shell.prompt = ft_strdup(str_tmp);
		free(str_tmp);
		add_history(shell.prompt);
		ft_lexer(&shell);
		ft_parser(&shell);
		ft_expander(&shell);
		//ft_print(&shell);
	}
	ft_clean_env_list(&shell);
	return (0);
}
