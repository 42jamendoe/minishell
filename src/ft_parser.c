/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

void ft_add_arg_list(t_arg *arg_list, t_arg *tmp_arg)
{
	t_arg *tmp_add_arg;

	tmp_add_arg = arg_list;
	if (!arg_list)
		arg_list = tmp_arg;
	else
	{
		while (tmp_add_arg)
			tmp_add_arg = tmp_add_arg->next;
		tmp_add_arg = tmp_arg;
	}
}

t_arg *ft_create_arg_list_item(char *prompt, int start)
{
	int len;
	t_arg *tmp_arg;

	tmp_arg = NULL;
	len = 0;
	while(prompt[len + start] != ' ')
		len++;
	tmp_arg = (t_arg *) malloc (sizeof(t_arg *));
	if (!tmp_arg)
		return (NULL);
	tmp_arg->arg_i = (char *) malloc (sizeof(char) * len + 1);
	if (!tmp_arg->arg_i)
		return (NULL);
	len = 0;
	while (prompt[start] != ' ')
	{
		tmp_arg->arg_i[len] = prompt[start];
		start++;
		len++;
	}
	tmp_arg->arg_i[len] = '\0';
	tmp_arg->next= NULL;
	return (tmp_arg);
}

t_arg *ft_create_arg_list(char *prompt, int i)
{
	t_arg *arg_list;
	t_arg *tmp_arg;

	arg_list = NULL;
	while (prompt[i] != '|' || prompt[i] != '\0')
	{
		printf("passazzz\n");
		tmp_arg = ft_create_arg_list_item(prompt, i);
		ft_add_arg_list(arg_list, tmp_arg);
		while (prompt[i] != ' ' || prompt[i] != '|' || prompt[i] != '\0')
			i++;
	}
	return (tmp_arg);
}
void ft_clean_token(t_token *list)
{
	t_token *tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

t_cmd *ft_create_cmd_item(t_token *list)
{
	int len;
	t_cmd *tmp_cmd;
	t_token *tmp_list;
	char **sim_cmd;
	int i;

	i = 0;
	tmp_list = list;
	while (tmp_list && tmp_list->type == WORD)
	{
		sim_cmd[i] = tmp_list->token;
		if (tmp_list->next && tmp_list->next->type == TOKEN && tmp_list->next->token != '|')
		{
			sim_cmd[i + 1] = ft_strjoin(tmp_list->token, tmp_list->next->token);
			free(tmp_list->token);
			free(tmp_list->next->token);
			tmp_list = tmp_list->next;
		}
		tmp_list = tmp_list->next;
	}	
	return (tmp_cmd);
}


void ft_add_cmd_item(t_cmd *cmd_list, t_cmd *tmp)
{
	if (!cmd_list)
		cmd_list = tmp;
	else
	{
		while (cmd_list)
			cmd_list = cmd_list->next;
		cmd_list->next = tmp;
	}
}

t_cmd *ft_parser(t_shell *shell)
{
	int i;
	t_cmd *cmd_list;
	t_cmd *tmp;

	i = 0;
	cmd_list = NULL;
	tmp_tkn = list;
	while (tmp_tkn)
	{
		tmp = ft_create_cmd_item(tmp_tkn);
		ft_add_cmd_item(cmd_list, tmp);
		if (tmp_tkn == '|')
			i++;
	}
	ft_clean_token(list);
	return (cmd_list);
}
