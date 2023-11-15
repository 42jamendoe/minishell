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

long long	g_status = 0;

int	ft_check_prompt(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (-1);
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
	{
		free(input);
		return (-1);
	}
	return (0);
}

void	ft_validate_program(int argc, char **argv)
{
	if (argc > 1 && *argv[1])
	{
		ft_putendl_fd("minishell: Type only <./minishell>", STDOUT_FILENO);
		exit (EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*prompt_tmp;

	ft_validate_program(argc, argv);
	ft_prepare_env(&shell, envp);
	while (1)
	{
		ft_config_signals();
		prompt_tmp = readline("minishell$");
		shell.prompt = ft_strdup(prompt_tmp);
		if (!shell.prompt)
			ft_clean(&shell, 1);
		free(prompt_tmp);
		if (!ft_check_prompt(shell.prompt))
		{
			add_history(shell.prompt);
			ft_lexer(&shell);
			ft_parser(&shell);
			ft_expander(&shell);
			ft_executor(&shell);
			free(shell.prompt);
		}
	}
	ft_clean(&shell, 1);
	return (0);
}
