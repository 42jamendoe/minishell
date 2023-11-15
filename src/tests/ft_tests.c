/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

// void	ft_print_args(t_cmd *comd)
// {
// 	int i;

// 	i = 0;
	// while (comd->sim_cmd[i])
	// {
	// 	printf("%d. %s %p\n", i , comd->sim_cmd[i], comd->sim_cmd[i]);
	// 	i++;
	// }
// 	printf("%d. %s %p\n", i , comd->sim_cmd[0], &comd->sim_cmd[0]);
// 	printf("%d. %s %p\n", i+1 , comd->sim_cmd[1], &comd->sim_cmd[1]);
// 	printf("%d. %s %p\n", i+2 , comd->sim_cmd[2], &comd->sim_cmd[2]);
// }

/*void ft_print_elements_token(t_shell *shell)
{
	t_token *list;
	int i = 1;

	list = shell->token_list;

	
	while (list)
	{
		printf("%d.	token:	*%s*				e name: *%d*\n", i, list->token_str, list->name);
		i++;
		list = list->next;
	}

}
void ft_print_arraydocomando(t_shell *shell)
{
 
	t_cmd	*apagar = shell->command_list;

	while (apagar)
	{
		if (!apagar->sim_cmd)
			printf("sem comando\n");
		else
		{
			int i = 0;
			while (apagar->sim_cmd[i])
			{
				printf("%s\n", apagar->sim_cmd[i]);
				i++;
			}
			apagar = apagar->next;
		}
	}
}

 void ft_print_arraydocomando(t_shell *shell)
{
	char **list;
	t_cmd *roda;
	int i = 1;
	roda = shell->command_list;

	if (!roda)
		printf("ja nao ha mais no comando\n");
	else
	{
		while (roda)
		{
			if (shell->command_list)
			{
				printf("ja nao ha mais\n");
				break;
			}
			else
			{
				list = shell->command_list->sim_cmd;
				int j = 0;
				while (list)
				{
					printf("%d.	comando	*%d*				e string: *%s*\n", i, j, list[j]);
					i++;
					j++;
				}
			}
			roda = roda->next;
		}
	}
} */
