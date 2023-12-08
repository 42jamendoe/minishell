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

int	g_status = 0;

int	ft_loop_prompt(t_shell *shell)
{
	if (ft_lexer(shell))
		return (EXIT_FAILURE);
	if (ft_parser(shell))
		return (EXIT_FAILURE);
	if (ft_expander(shell))
		return (EXIT_FAILURE);
	if (ft_executor(shell))
		return (EXIT_FAILURE);
	ft_clean_prompt(shell);
	return (0);
}

int	ft_check_prompt(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (EXIT_FAILURE);
	while (input[i] == ' ')
		i++;
	if (input[i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_validate_program(t_shell *shell, int argc, char **argv)
{
	if (argc > 1 && *argv[1])
	{
		ft_putendl_fd("minishell: type only <./minishell>", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	shell->cmd_nbr = 0;
	shell->command_list = NULL;
	shell->env = NULL;
	shell->prompt = NULL;
	shell->token_list = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*prompt_tmp;

	ft_validate_program(&shell, argc, argv);
	ft_prepare_env(&shell, envp);
	while (1)
	{
		ft_config_signals(&shell);
		prompt_tmp = readline("minishell$ ");
		if (!prompt_tmp)
			exit(EXIT_FAILURE);
		else
		{
			shell.prompt = ft_strdup(prompt_tmp);
			free(prompt_tmp);
			if (!shell.prompt)
				ft_putendl_fd("minishell: error getting line", STDERR_FILENO);
			else if (!ft_check_syntax(&shell))
				ft_loop_prompt(&shell);
		}
	}
}
