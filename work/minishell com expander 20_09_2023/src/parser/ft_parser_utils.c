/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	ft_cmd_arg_nbr(t_token *index)
{
	int	i;

	i = 0;
	while (index)
	{
		if (index->type == PIPE)
			return (i);
		else if (index->type == WORD)
			i++;
		else
			i--;
		index = index->next;
	}
	return (i);
}

void	ft_pipe_clean(t_shell *shell)
{
	t_token	*tmp_pipe;

	tmp_pipe = shell->tkn_list->next;
	free(shell->tkn_list->token);
	free(shell->tkn_list);
	shell->tkn_list = tmp_pipe;
}

int	ft_validate_cmd(char *str)
{
	if (!ft_strncmp(str, "echo", 5))
		return (0);
	else if (!ft_strncmp(str, "cd", 3))
		return (1);
	else if (!ft_strncmp(str, "pwd", 4))
		return (2);
	else if (!ft_strncmp(str, "export", 7))
		return (3);
	else if (!ft_strncmp(str, "unset", 6))
		return (4);
	else if (!ft_strncmp(str, "env", 4))
		return (5);
	else if (!ft_strncmp(str, "exit", 5))
		return (6);
	else
		return (-1);
}

void ft_print(t_shell *shell)
{
	int i = 0;
	int j = 1; //Numero de comandos
	int z = 0;
	t_cmd *tmpjoao;
	tmpjoao = shell->cmd_list;
	while (tmpjoao->next)
	{
		tmpjoao = tmpjoao->next;
		j++;
	}
	tmpjoao = shell->cmd_list;
	while (i < j)
	{
		i++;
		z = 0;
		while (z < tmpjoao->arg_nbr)
		{
		printf("%s\n",tmpjoao->sim_cmd[z]);
		z++;
		}
		printf("\n");
		tmpjoao = tmpjoao->next;
	}
}