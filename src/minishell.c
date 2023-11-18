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

int	ft_loop_prompt(t_shell *shell)
{
	add_history(shell->hist);
	free(shell->hist);
	ft_lexer(shell);
	ft_parser(shell);
	ft_expander(shell);
	ft_executor(shell);
	ft_clean_prompt(shell);
	return (0);
}

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
	int		bad;

	bad = 0;
	ft_validate_program(argc, argv);
	ft_prepare_env(&shell, envp);
	while (1)
	{
		ft_config_signals();
		prompt_tmp = readline("minishell$");
		if (!prompt_tmp)
			exit(EXIT_SUCCESS);
		else
		{
			shell.prompt = ft_strdup(prompt_tmp);
			shell.hist = ft_strdup(prompt_tmp);
			if (!shell.prompt || !shell.hist)
				bad = ft_error_getting_line(&shell);
			free(prompt_tmp);	
			if (!ft_check_syntax(&shell) && !bad)
				ft_loop_prompt(&shell);
		}
	}
	ft_clean_exit(&shell);
	return (EXIT_SUCCESS);
}
