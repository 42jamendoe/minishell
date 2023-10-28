/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_name	ft_check_char(char *prompt, int i)
{
	t_token_name	token_name;

	if (prompt[i] == '|')
		token_name = PIPE;
	else if (prompt[i] == '>')
	{
		if (prompt[i + 1] == '>')
			token_name = GREATGREAT;
		else
			token_name = GREAT;
	}
	else if (prompt[i] == '<')
	{
		if (prompt[i + 1] == '<')
			token_name = LESSLESS;
		else
			token_name = LESS;
	}
	else
		token_name = WORD;
	return (token_name);
}

int	ft_create_token(t_shell *shell, int i, t_token_name name)
{
	char	*tmp_token;
	t_token	*new_token;
	int		j;

	j = 2;
	if ((shell->prompt[i + 1] == '<' || shell->prompt[i + 1] == '>') && \
	shell->prompt[i] == shell->prompt[i + 1])
	{
		j++;
		tmp_token = (char *) malloc (sizeof(char) * 2 + 1);
		if (!tmp_token)
			ft_clean();
		tmp_token[0] = shell->prompt[i];
		tmp_token[1] = shell->prompt[i + 1];
		tmp_token[2] = '\0';
	}
	else
	{
		tmp_token = (char *) malloc (sizeof(char) * 1 + 1);
		if (!tmp_token)
			ft_clean();
		tmp_token[0] = shell->prompt[i];
		tmp_token[1] = '\0';
	}
	new_token = ft_create_item(tmp_token, name);
	ft_add_new(shell, new_token);
	return (j);
}

int	ft_create_word(t_shell *shell, int i)
{
	int		j;
	char	*word_tmp;
	t_token	*new_word;

	j = 0;
	if (shell->prompt[i + j] && (shell->prompt[i + j] == '\'' \
	|| shell->prompt[i + j] == '"'))
		j += ft_handle_quotes(shell->prompt, i, shell->prompt[i]);
	else
	{
		while (shell->prompt[i + j] && shell->prompt[i + j] != ' ' && \
		shell->prompt[i + j] != '<' && shell->prompt[i + j] != '>' && \
		shell->prompt[i + j] != '|')
			j++;
	}
	word_tmp = ft_substr(&shell->prompt[i], 0, j);
	if (!word_tmp)
		ft_clean();
	new_word = ft_create_item(word_tmp, WORD);
	ft_add_new(shell, new_word);
	return (j);
}

void	ft_lexer(t_shell *shell)
{
	int				i;
	t_token_name	token_tmp;

	i = 0;
	shell->token_list = NULL;
	while (shell->prompt[i])
	{
		while (shell->prompt[i] == ' ')
			i++;
		token_tmp = ft_check_char(shell->prompt, i);
		if (token_tmp == WORD)
			i += ft_create_word(shell, i);
		else
			i += ft_create_token(shell, i, token_tmp);
	}
	shell->cmd_nbr = ft_command_number(shell) + 1;
}

void ft_print_elements_token(t_shell *shell)
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
 
	t_cmd *apagar = shell->command_list;

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


/* void ft_print_arraydocomando(t_shell *shell)
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
