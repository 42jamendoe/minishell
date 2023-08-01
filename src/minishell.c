/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <editline/readline.h>
#include <stddef.h>

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	t_env	*tmp;
	t_token	*main_list;
	char	*prompt;
	int		i;

	env_list = NULL;
	i = 0;
	if (argc > 1 && *argv)
		exit(EXIT_FAILURE);
	while (envp[i])
	{
		tmp = ft_new_env_item(envp[i]);
		env_list = ft_add_new_item(env_list, tmp);
		i++;
	}
	while (1)
	{
		prompt = readline("minishell$");
		main_list = ft_lexer(prompt);
	}
	ft_clean_env_list(env_list);
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