/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_process_text(char *arg, int *anchor, int *position)
{
	char *tmp_3;
	int size;

	size = position - anchor;
	while (arg[*position] && arg[*position] != '$')
		(*position)++;
	tmp_3 = ft_substr(arg, *anchor, size - 1);
	*anchor = *position;
	return (tmp_3);
}

char	*ft_process_var(t_shell *shell, char *arg, int *anchor, int *position)
{
	char *tmp_3;

	while (arg[(*position) + 1] && arg[(*position) + 1] != '$')
		(*position)++;
	if (arg[(*position)] == '\0')
		return (NULL);
	if (arg[(*position)] == '?')
	{
		tmp_3 = ft_strdup("O dolar com ponto de interrogacao nao esta implementado");
		return(tmp_3);
	}
	(*anchor) += 1;
	tmp_3 = ft_expand_dollar(shell, arg, &(*anchor), &(*position));
	*anchor = *position;
	return (tmp_3);
}

char	*ft_process(t_shell *shell, char *arg)
{
	char	*new_expanded;
	char	*tmp_1;
	char	*tmp_2;
	int		anchor;
	int		position;

	anchor = 0;
	position = 0;
	new_expanded = ft_strdup("\0");
	while(arg[position] != '\0')
	{
		if (arg[position] != '$')
			tmp_1 = ft_process_text(arg, &anchor, &position);
		else
			tmp_1 = ft_process_var(shell, arg, &anchor, &position);
		tmp_2 = ft_strjoin(new_expanded, tmp_1);
		free(new_expanded);
		new_expanded = tmp_2;
	}
	return (new_expanded);
}

char	*ft_expand_char(t_shell *shell, char *arg)
{
	t_status	arg_status;
	char		*expanded;
	char		*tmp_trim;

	arg_status = ft_define_status(arg[0]);
	if (arg_status == DEFAULT)
		expanded = ft_process(shell, arg);
	if (arg_status == SQUOTE)
		expanded = ft_strtrim(arg, "\'");
	if (arg_status == DQUOTE)
	{
		tmp_trim = ft_strtrim(arg, "\"");
		expanded = ft_process(shell, tmp_trim);
		free(tmp_trim);
	}
	return (expanded);
}

void	ft_expander(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	t_cmd	cmd_exp;
	char	*tmp_exp_arg;
	int		arg_count;

	cmd_exp.arg_nbr = shell->cmd_list->arg_nbr;
	tmp_cmd = shell->cmd_list;
	while (tmp_cmd)
	{
		cmd_exp.sim_cmd = (char **) malloc (sizeof(char *) * shell->cmd_list->arg_nbr);
		cmd_exp.sim_cmd[0] = ft_strdup(tmp_cmd->sim_cmd[0]);
		arg_count = 1;
		while (arg_count < shell->cmd_list->arg_nbr)
		{
			tmp_exp_arg = ft_expand_char(shell, tmp_cmd->sim_cmd[arg_count]);
			printf("cmd expanded: %s\n", tmp_exp_arg);
			cmd_exp.sim_cmd[arg_count] = tmp_exp_arg;
			arg_count++;
		}	
		tmp_cmd = tmp_cmd->next;
	}
}
