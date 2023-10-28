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

long long	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*prompt_tmp;

	shell.env = NULL;
	if (argc > 1 && *argv[1])
	{
		ft_putendl_fd("minishell: Type only <./minishell>", STDOUT_FILENO);
		return (0);
	}
	if (ft_create_env(&shell, envp))
	{
		ft_putendl_fd("minishell: Can't create environment", STDOUT_FILENO);
		return (1);
	}
	while (1)
	{
		//ft_config_signals();
		prompt_tmp = readline("minishell$");
		shell.prompt = ft_strdup(prompt_tmp);
		if (!shell.prompt)
			ft_clean();
		free(prompt_tmp);
		if (shell.prompt[0] != '\0')
		{
			add_history(shell.prompt);
			ft_lexer(&shell);
			ft_parser(&shell);
			ft_expander(&shell);
			
			ft_executor(&shell);
			free(shell.prompt);
		}
	}
	return (0);
}
