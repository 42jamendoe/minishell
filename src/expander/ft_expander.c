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

//long long	g_status;

char	*ft_expand_text(char *arg, int anchor, int position)
{
	char	*tmp_text;
	int		len;

	len = position - anchor;
	tmp_text = ft_substr(arg, anchor, len);
	return (tmp_text);
}

char	*ft_expand_var(char *arg, int anchor, int position)
{
	char	*expanded;

	// if (arg[anchor + 1] == '\?')
	// {
	// 	expanded = ft_lltoa(g_status);
	// 	if (!expanded)
	// 		ft_clean();
	// 	return (expanded);
	// }
	anchor += 1;
	expanded = ft_expand_dollar(arg, anchor, position);
	if (!expanded)
		ft_clean();
	return (expanded);
}

char	*ft_process_arg(char *arg, int anchor, int position)
{
	char	*substr_expanded;

	if (arg[anchor] != '$')
		substr_expanded = ft_expand_text(arg, anchor, position);
	else
		substr_expanded = ft_expand_var(arg, anchor, position);
	return (substr_expanded);
}

char	*ft_expand_arg(char *arg, int *position)
{
	t_state		arg_state;
	char		*expanded;
	char		*tmp_trimmed;
	int			anchor;

	arg_state = ft_define_state(arg[(*position)]);
	if (arg_state == DEFAULT)
	{
		anchor = (*position);
		while (arg[(*position)] != '\0' && arg[(*position)] != '\'' \
		&& arg[(*position)] != '\"')
			(*position)++;
		expanded = ft_process_arg(arg, anchor, (*position));
		if (arg[(*position)])
			(*position)++;
	}
	else if (arg_state == SQUOTE)
		expanded = ft_strtrim(arg, "\'");
	else if (arg_state == DQUOTE)
	{
		tmp_trimmed = ft_strtrim(arg, "\"");
		while (arg[(*position)] != '\0' && arg[(*position)] != '\'' \
		&& arg[(*position)] != '\"')
			(*position)++;
		expanded = ft_process_arg(tmp_trimmed, 0, (*position));
		free(tmp_trimmed);
	}
	else
		expanded = NULL;
	return (expanded);
}

void	ft_expander(t_shell *shell)
{
	t_cmd	*tmp_command;
	char	*tmp_word;
	int		arg_count;
	int 	position;
	char	*tmp1;
	char	*tmp2;
	tmp_command = shell->command_list;

	while (tmp_command)
	{
		arg_count = 1;
		while (tmp_command->sim_cmd[arg_count])
		{
			position = 0;
			tmp1 = ft_strdup("\0");
			while (tmp_command->sim_cmd[arg_count][position] != '\0')
			{
				tmp_word = ft_expand_arg(tmp_command->sim_cmd[arg_count], &position);
				tmp2 = ft_strjoin(tmp1, tmp_word);
				free(tmp1);
				if (arg_count < tmp_command->arg_nbr - 2)
					free(tmp_word);
				if (!tmp2)
					ft_clean();
				tmp1 = tmp2;
			}
			tmp_command->sim_cmd[arg_count] = tmp1;
			arg_count++;
		}
		tmp_command = tmp_command->next;
	}
}

/*  	int i = 0;
	t_cmd *apagar = shell->command_list;
	if (!shell->command_list)
	{
		// printf("sem comando\n");
	}
	else
	{
	while (apagar)
	{
		while (shell->command_list->sim_cmd[i])
			i++;
		// printf("%s\n", shell->command_list->sim_cmd[i]);
		apagar = apagar->next;
	}
	} */