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
	t_shell shell;
	int		i;

	shell.env_list = NULL;
	i = 0;
	if (argc > 1 && *argv)
		exit(EXIT_FAILURE);
	while (envp[i])
	{
		shell.tmp = ft_new_env_item(envp[i]);
		ft_add_new_item(&shell);
		i++;
	}
	while (1)
	{
		shell.prompt = readline("minishell$");
		ft_lexer(&shell);
	}
	ft_clean_env_list(&shell);
	return (0);
}

/*		cmd_tmp = cmd_list;
 		while (cmd_tmp)
		{
			printf("%s\n", cmd_tmp->sim_cmd);
			arg_tempo = cmd_tmp->cmd_arg;
			while (arg_tempo)
			{
				printf("%s\n", arg_tempo->arg_i);
				arg_tempo = arg_tempo->next;
			}
			cmd_tmp = cmd_tmp->next;
		} */